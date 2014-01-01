#!/usr/bin/perl

# Copyright (C) Paulo Custodio, 2011-2013
#
# $Header: /home/dom/z88dk-git/cvs/z88dk/src/z80asm/lib/t/Attic/strutil.t,v 1.4 2014-01-01 21:16:20 pauloscustodio Exp $
#
# Test strutil.c

use Modern::Perl;
use Test::More;
use File::Slurp;
use Capture::Tiny 'capture';
use Test::Differences; 

my $compile = "cc -Wall -mms-bitfields -IC:/MinGW/msys/1.0/include/glib-2.0 -IC:/MinGW/msys/1.0/lib/glib-2.0/include -otest test.c strutil.c class.c die.c xmalloc.c -LC:/MinGW/msys/1.0/lib -lglib-2.0 -lintl";

warn "-mms-bitfields -IC:/MinGW/msys/1.0/include/glib-2.0 -IC:/MinGW/msys/1.0/lib/glib-2.0/include -LC:/MinGW/msys/1.0/lib -lglib-2.0 -lintl";

write_file("test.1.asm", {binmode => ':raw'}, "");
write_file("test.2.asm", {binmode => ':raw'}, "A\nB\rC\r\nD\n\rE");
write_file("test.3.asm", {binmode => ':raw'}, "A\nB\rC\r\nD\n\rE\n");
write_file("test.4.asm", {binmode => ':raw'}, "A\nB\rC\r\nD\n\rE\r");
write_file("test.5.asm", {binmode => ':raw'}, "A\nB\rC\r\nD\n\rE\r\n");
write_file("test.6.asm", {binmode => ':raw'}, "A\nB\rC\r\nD\n\rE\n\r");
write_file("test.7.asm", {binmode => ':raw'}, "x" x 1100);
write_file("test.8.asm", {binmode => ':raw'}, "ABCDEFGHIJ\nabcdefghij\n");

write_file("test.c", <<'END');
#include "die.h"
#include "strutil.h"

#define ERROR die("Test failed at line %d\n", __LINE__)
#define FOPEN(file)		fp = fopen((file), "rb"); if (fp == NULL) ERROR;
#define GETLINE(s,exp_text,exp_ret) \
						{ BOOL ret = Str_getline((s), fp); \
						  if (ret != exp_ret) ERROR; \
						  if (strcmp((s)->str, exp_text)) ERROR; \
						}
#define GETCHARS(s,num,exp_text,exp_ret) \
						{ BOOL ret = Str_getchars((s), fp, (num)); \
						  if (ret != exp_ret) ERROR; \
						  if (strcmp((s)->str, exp_text)) ERROR; \
						}
#define FCLOSE()		fclose(fp);
#define GET_ABCDE(s,file) FOPEN((file)); \
						GETLINE((s),"A\n",TRUE); \
						GETLINE((s),"B\n",TRUE); \
						GETLINE((s),"C\n",TRUE); \
						GETLINE((s),"D\n",TRUE); \
						GETLINE((s),"E\n",TRUE); \
						GETLINE((s),"",   FALSE); \
						FCLOSE();

void _check_str(Str *str, size_t size, size_t len, char *text, BOOL alloc_str,
				char *file, int lineno)
{
	if (str == NULL) 
		warn("%s(%d) str == NULL\n", file, lineno);
	if (str->str == NULL) 
		warn("%s(%d) str->str == NULL\n", file, lineno);
	if (str->size != size)
		warn("%s(%d) str->size %u != %u\n", file, lineno, str->size, size);
	if (str->len != len)
		warn("%s(%d) str->len %u != %u\n", file, lineno, str->len, len);
	if (str->str[str->len] != 0)
		warn("%s(%d) null terminator not found\n", file, lineno);
	if (memcmp(str->str, text, str->len))
		warn("%s(%d) different text found\n", file, lineno);
	if (str->alloc_str != alloc_str)
		warn("%s(%d) str->alloc_str %d != %d\n", file, lineno, str->alloc_str, alloc_str);
}	

#define check_str(str,size,len,text,alloc_str)	\
       _check_str(str,size,len,text,alloc_str,__FILE__,__LINE__)

void call_vsprintf (Str *str, char *format, ...)
{
	va_list argptr;
	va_start(argptr, format);
	Str_vsprintf(str, format, argptr);
}

void call_append_vsprintf (Str *str, char *format, ...)
{
	va_list argptr;
	va_start(argptr, format);
	Str_append_vsprintf(str, format, argptr);
}

Str * static_s1;
DEFINE_STR( static_s2, 5 );

int main()
{
	char s[255];
	char * p;

	/* strtoupper, strtolower */
	strcpy(s, "Abc1");
	p = strtolower(s);
	if (p != s)							ERROR;
	if(strcmp(s, "abc1"))				ERROR;
	
	strcpy(s, "Abc1");
	p = strtoupper(s);
	if (p != s)							ERROR;
	if(strcmp(s, "ABC1"))				ERROR;
	
	/* stricompare */
	if (stricompare("","") != 0)		ERROR;
	if (stricompare("a","") < 1)		ERROR;
	if (stricompare("","a") > -1)		ERROR;
	if (stricompare("a","a") != 0)		ERROR;
	if (stricompare("a","A") != 0)		ERROR;
	if (stricompare("A","a") != 0)		ERROR;
	if (stricompare("ab","a") < 1)		ERROR;
	if (stricompare("a","ab") > -1)		ERROR;
	if (stricompare("ab","ab") != 0)	ERROR;
	
	
	/* chomp, Str_chomp */
	{
		Str *s1 = OBJ_NEW(Str);
		
		strcpy(s, "\r\n \t\fx\r\n \t\f");
		Str_set( s1, s );
		
		p = chomp(s);
		if (p != s)							ERROR;
		if(strcmp(s, "\r\n \t\fx"))			ERROR;
		
		Str_chomp(s1);
		if(strcmp(s, s1->str))				ERROR;
	
		strcpy(s, "\r\n \t\f \r\n \t\f");
		Str_set( s1, s );

		p = chomp(s);
		if (p != s)							ERROR;
		if(strcmp(s, ""))					ERROR;

		Str_chomp(s1);
		if(strcmp(s, s1->str))				ERROR;
	}
	
	/* Str */
	{
		Str *s1 = OBJ_NEW(Str);
		Str *s2;
		char buffer[5] = "";
		Str _s3 = INIT_STR( buffer ), *s3 = & _s3;
		DEFINE_STR( s4, 10 );

		check_str( s1, 256, 0, "", TRUE);
		check_str( s3,   5, 0, "", FALSE);
		check_str( s4,  10, 0, "", FALSE);

		/* unreserve */
		Str_unreserve( s1 );
		Str_unreserve( s3 );
		Str_unreserve( s4 );

		check_str( s1,   1, 0, "", TRUE);
		check_str( s3,   5, 0, "", FALSE);
		check_str( s4,  10, 0, "", FALSE);


		Str_clear( s1 ); Str_unreserve( s1 );
		Str_clear( s3 ); Str_unreserve( s3 );
		Str_clear( s4 ); Str_unreserve( s4 );

		
		/* append char */
		Str_append_char( s1, 0 );
		Str_append_char( s3, 0 );
		Str_append_char( s4, 0 );

		check_str( s1, 256, 1, "\0", TRUE);
		check_str( s3,   5, 1, "\0", FALSE);
		check_str( s4,  10, 1, "\0", FALSE);

		Str_append_char( s1, 1 );
		Str_append_char( s3, 1 );
		Str_append_char( s4, 1 );

		check_str( s1, 256, 2, "\0\1", TRUE);
		check_str( s3,   5, 2, "\0\1", FALSE);
		check_str( s4,  10, 2, "\0\1", FALSE);

		Str_append_char( s1, 2 );
		Str_append_char( s3, 2 );
		Str_append_char( s4, 2 );

		check_str( s1, 256, 3, "\0\1\2", TRUE);
		check_str( s3,   5, 3, "\0\1\2", FALSE);
		check_str( s4,  10, 3, "\0\1\2", FALSE);

		Str_append_char( s1, 3 );
		Str_append_char( s3, 3 );
		Str_append_char( s4, 3 );

		check_str( s1, 256, 4, "\0\1\2\3", TRUE);
		check_str( s3,   5, 4, "\0\1\2\3", FALSE);
		check_str( s4,  10, 4, "\0\1\2\3", FALSE);

		Str_append_char( s1, 4 );
		Str_append_char( s3, 4 );
		Str_append_char( s4, 4 );

		check_str( s1, 256, 5, "\0\1\2\3\4", TRUE);
		check_str( s3,   5, 4, "\0\1\2\3",   FALSE);
		check_str( s4,  10, 5, "\0\1\2\3\4", FALSE);


		Str_clear( s1 ); Str_unreserve( s1 );
		Str_clear( s3 ); Str_unreserve( s3 );
		Str_clear( s4 ); Str_unreserve( s4 );

		/* append */
		Str_append( s1, "h" );
		Str_append( s3, "h" );
		Str_append( s4, "h" );

		check_str( s1, 256, 1, "h", TRUE);
		check_str( s3,   5, 1, "h", FALSE);
		check_str( s4,  10, 1, "h", FALSE);

		Str_append_bytes( s1, "el\0o", 4 );
		Str_append_bytes( s3, "el\0o", 4 );
		Str_append_bytes( s4, "el\0o", 4 );

		check_str( s1, 256, 5, "hel\0o", TRUE);
		check_str( s3,   5, 4, "hel\0",  FALSE);
		check_str( s4,  10, 5, "hel\0o", FALSE);

		Str_append_char( s1, 32 );
		Str_append_char( s3, 32 );
		Str_append_char( s4, 32 );

		check_str( s1, 256, 6, "hel\0o ", TRUE);
		check_str( s3,   5, 4, "hel\0",   FALSE);
		check_str( s4,  10, 6, "hel\0o ", FALSE);

		Str_append( s1, "world" );
		Str_append( s3, "world" );
		Str_append( s4, "world" );

		check_str( s1, 256, 11, "hel\0o world", TRUE);
		check_str( s3,   5,  4, "hel\0",        FALSE);
		check_str( s4,  10,  9, "hel\0o wor",   FALSE);


		Str_clear( s1 ); Str_unreserve( s1 );
		Str_clear( s3 ); Str_unreserve( s3 );
		Str_clear( s4 ); Str_unreserve( s4 );


		/* set */
		Str_set( s1, "X" );
		Str_set( s3, "X" );
		Str_set( s4, "X" );

		check_str( s1, 256, 1, "X", TRUE);
		check_str( s3,   5, 1, "X", FALSE);
		check_str( s4,  10, 1, "X", FALSE);

		Str_set_bytes( s1, "\0\1", 2 );
		Str_set_bytes( s3, "\0\1", 2 );
		Str_set_bytes( s4, "\0\1", 2 );

		check_str( s1, 256, 2, "\0\1", TRUE);
		check_str( s3,   5, 2, "\0\1", FALSE);
		check_str( s4,  10, 2, "\0\1", FALSE);

		Str_set_char( s1, 33 );
		Str_set_char( s3, 33 );
		Str_set_char( s4, 33 );

		check_str( s1, 256, 1, "!", TRUE);
		check_str( s3,   5, 1, "!", FALSE);
		check_str( s4,  10, 1, "!", FALSE);


		Str_clear( s1 ); Str_unreserve( s1 );
		Str_clear( s3 ); Str_unreserve( s3 );
		Str_clear( s4 ); Str_unreserve( s4 );


		/* clear */
		Str_clear( s1 );
		Str_clear( s3 );
		Str_clear( s4 );

		check_str( s1,   1, 0, "", TRUE);
		check_str( s3,   5, 0, "", FALSE);
		check_str( s4,  10, 0, "", FALSE);
		

		Str_clear( s1 ); Str_unreserve( s1 );
		Str_clear( s3 ); Str_unreserve( s3 );
		Str_clear( s4 ); Str_unreserve( s4 );
		

		/* reserve in 256-byte blocks */
		Str_reserve( s1, 255 );
		Str_reserve( s3, 255 );
		Str_reserve( s4, 255 );
		
		check_str( s1, 256, 0, "", TRUE);
		check_str( s3,   5, 0, "", FALSE);
		check_str( s4,  10, 0, "", FALSE);
			
		Str_reserve( s1, 256 );
		Str_reserve( s3, 256 );
		Str_reserve( s4, 256 );
		
		check_str( s1, 512, 0, "", TRUE);
		check_str( s3,   5, 0, "", FALSE);
		check_str( s4,  10, 0, "", FALSE);
			
		Str_reserve( s1, 511 );
		Str_reserve( s3, 511 );
		Str_reserve( s4, 511 );
		
		check_str( s1, 512, 0, "", TRUE);
		check_str( s3,   5, 0, "", FALSE);
		check_str( s4,  10, 0, "", FALSE);

		
		Str_clear( s1 ); Str_unreserve( s1 );
		Str_clear( s3 ); Str_unreserve( s3 );
		Str_clear( s4 ); Str_unreserve( s4 );
		

		/* clone */
		Str_set( s1, "hello" );
		Str_set( s3, "hello" );
		Str_set( s4, "hello" );
		
		check_str( s1, 256, 5, "hello", TRUE);
		check_str( s3,   5, 4, "hell",  FALSE);
		check_str( s4,  10, 5, "hello", FALSE);

		s2 = Str_clone( s1 );
		check_str( s2, 256, 5, "hello", TRUE);
		if (s1 == s2)					ERROR;
		if (s1->str == s2->str)			ERROR;
		OBJ_DELETE( s2 );
		if (s2)							ERROR;


		Str_clear( s1 ); Str_unreserve( s1 );
		Str_clear( s3 ); Str_unreserve( s3 );
		Str_clear( s4 ); Str_unreserve( s4 );
		
		
		/* sprintf */
		Str_sprintf( s1, "%s %d", "hello", 123);
		Str_sprintf( s3, "%s %d", "hello", 123);
		Str_sprintf( s4, "%s %d", "hello", 123);
		
		check_str( s1, 256, 9, "hello 123", TRUE);
		check_str( s3,   5, 4, "hell",      FALSE);
		check_str( s4,  10, 9, "hello 123", FALSE);

		/* append_sprintf */
		Str_append_sprintf( s1, "%s", "");	/* empty */
		Str_append_sprintf( s3, "%s", "");	/* empty */
		Str_append_sprintf( s4, "%s", "");	/* empty */
		
		check_str( s1, 256, 9, "hello 123", TRUE);
		check_str( s3,   5, 4, "hell",      FALSE);
		check_str( s4,  10, 9, "hello 123", FALSE);

		Str_append_sprintf( s1, "%s", " and world");
		Str_append_sprintf( s3, "%s", " and world");
		Str_append_sprintf( s4, "%s", " and world");
		
		check_str( s1, 256, 19, "hello 123 and world", TRUE);
		check_str( s3,   5,  4, "hell",                FALSE);
		check_str( s4,  10,  9, "hello 123",           FALSE);


		Str_clear( s1 ); Str_unreserve( s1 );
		Str_clear( s3 ); Str_unreserve( s3 );
		Str_clear( s4 ); Str_unreserve( s4 );


		/* vsprintf */
		call_vsprintf( s1, "%s %d", "hello", 123);
		call_vsprintf( s3, "%s %d", "hello", 123);
		call_vsprintf( s4, "%s %d", "hello", 123);
		
		check_str( s1, 256, 9, "hello 123", TRUE);
		check_str( s3,   5, 4, "hell",      FALSE);
		check_str( s4,  10, 9, "hello 123", FALSE);
		
		/* append_vsprintf */
		call_append_vsprintf( s1, "%s", "");	/* empty */
		call_append_vsprintf( s3, "%s", "");	/* empty */
		call_append_vsprintf( s4, "%s", "");	/* empty */
		
		check_str( s1, 256, 9, "hello 123", TRUE);
		check_str( s3,   5, 4, "hell",      FALSE);
		check_str( s4,  10, 9, "hello 123", FALSE);
		
		call_append_vsprintf( s1, "%s", " and world");
		call_append_vsprintf( s3, "%s", " and world");
		call_append_vsprintf( s4, "%s", " and world");

		check_str( s1, 256, 19, "hello 123 and world", TRUE);
		check_str( s3,   5,  4, "hell",                FALSE);
		check_str( s4,  10,  9, "hello 123",           FALSE);


		Str_clear( s1 ); Str_unreserve( s1 );
		Str_clear( s3 ); Str_unreserve( s3 );
		Str_clear( s4 ); Str_unreserve( s4 );


		/* unreserve and sprintf */
		Str_sprintf( s1, "%d", 12345 );
		Str_sprintf( s3, "%d", 12345 );
		Str_sprintf( s4, "%d", 12345 );
		
		check_str( s1, 256, 5, "12345", TRUE);
		check_str( s3,   5, 4, "1234",  FALSE);
		check_str( s4,  10, 5, "12345", FALSE);
	}
	
	/* static */
	{
		Str * p;

		p = INIT_OBJ( Str, &static_s1 );
		if (! p)						ERROR;
		if (p != static_s1)				ERROR;
		
		p = INIT_OBJ( Str, &static_s1 );
		if (! p)						ERROR;
		if (p != static_s1)				ERROR;
		
		Str_set( static_s1, "1234567890" );
		Str_set( static_s2, "1234567890" );

		check_str( static_s1, 256, 10, "1234567890", TRUE);
		check_str( static_s2,   5,  4, "1234",       FALSE);
	}
	
	/* getline */
	{
		Str *s1 = OBJ_NEW(Str);
		DEFINE_STR( s2, 10 );
		FILE * fp;
	
		FOPEN("test.1.asm");
		GETLINE( s1, "", FALSE);
		FCLOSE();
		
		FOPEN("test.1.asm");
		GETLINE( s2, "", FALSE);
		FCLOSE();
		
		GET_ABCDE( s1, "test.2.asm" );
		GET_ABCDE( s1, "test.3.asm" );
		GET_ABCDE( s1, "test.4.asm" );
		GET_ABCDE( s1, "test.5.asm" );
		GET_ABCDE( s1, "test.6.asm" );

		GET_ABCDE( s2, "test.2.asm" );
		GET_ABCDE( s2, "test.3.asm" );
		GET_ABCDE( s2, "test.4.asm" );
		GET_ABCDE( s2, "test.5.asm" );
		GET_ABCDE( s2, "test.6.asm" );

		FOPEN("test.7.asm");
		GETLINE( s1, 
				"xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx"
				"xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx"
				"xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx"
				"xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx"
				"xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx"
				"xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx"
				"xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx"
				"xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx"
				"xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx"
				"xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx"
				"xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx"
				"xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx"
				"xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx"
				"xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx"
				"xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx"
				"xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx"
				"xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx"
				"xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx"
				"xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx"
				"xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx"
				"xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx"
				"xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx" "xxxxxxxxxx"
				"\n", TRUE);
		GETLINE( s1, "", FALSE);
		FCLOSE();
		
		FOPEN("test.7.asm");
		GETLINE( s2, "xxxxxxxxx", TRUE);
		GETLINE( s2, "", FALSE);
		FCLOSE();
	}
		
	/* getchars */
	{
		Str *s1 = OBJ_NEW(Str);
		DEFINE_STR( s2, 10 );
		DEFINE_STR( s3,  3 );
		FILE *fp;

		FOPEN("test.8.asm");
		GETCHARS( s1, 3, "ABC",  TRUE );
		GETCHARS( s1, 3, "DEF",  TRUE );
		GETCHARS( s1, 3, "GHI",  TRUE );
		GETCHARS( s1, 3, "J\na", TRUE );
		GETCHARS( s1, 3, "bcd",  TRUE );
		GETCHARS( s1, 3, "efg",  TRUE );
		GETCHARS( s1, 3, "hij",  TRUE );
		GETCHARS( s1, 3, "\n",   FALSE );
		FCLOSE();

		FOPEN("test.8.asm");
		GETCHARS( s2, 3, "ABC",  TRUE );
		GETCHARS( s2, 3, "DEF",  TRUE );
		GETCHARS( s2, 3, "GHI",  TRUE );
		GETCHARS( s2, 3, "J\na", TRUE );
		GETCHARS( s2, 3, "bcd",  TRUE );
		GETCHARS( s2, 3, "efg",  TRUE );
		GETCHARS( s2, 3, "hij",  TRUE );
		GETCHARS( s2, 3, "\n",   FALSE );
		FCLOSE();

		FOPEN("test.8.asm");
		GETCHARS( s3, 3, "AB",  TRUE );
		GETCHARS( s3, 3, "DE",  TRUE );
		GETCHARS( s3, 3, "GH",  TRUE );
		GETCHARS( s3, 3, "J\n", TRUE );
		GETCHARS( s3, 3, "bc",  TRUE );
		GETCHARS( s3, 3, "ef",  TRUE );
		GETCHARS( s3, 3, "hi",  TRUE );
		GETCHARS( s3, 3, "\n",  FALSE );
		FCLOSE();
	}
	
	return 0;
}
END
system($compile) and die "compile failed: $compile\n";

t_capture("test", "", "", 0);

unlink <test.*>;
done_testing;

sub t_capture {
	my($cmd, $exp_out, $exp_err, $exp_exit) = @_;
	my $line = "[line ".((caller)[2])."]";
	ok 1, "$line command: $cmd";
	
	my($out, $err, $exit) = capture { system $cmd; };
	eq_or_diff_text $out, $exp_out, "$line out";
	eq_or_diff_text $err, $exp_err, "$line err";
	ok !!$exit == !!$exp_exit, "$line exit";
}


# $Log: strutil.t,v $
# Revision 1.4  2014-01-01 21:16:20  pauloscustodio
# Of-by-one error
#
# Revision 1.3  2013/12/30 02:05:34  pauloscustodio
# Merge dynstr.c and safestr.c into lib/strutil.c; the new Str type
# handles both dynamically allocated strings and fixed-size strings.
# Replaced g_strchomp by chomp by; g_ascii_tolower by tolower;
# g_ascii_toupper by toupper; g_ascii_strcasecmp by stricompare.
#
# Revision 1.2  2013/12/26 23:42:27  pauloscustodio
# Replace StringList from strutil by StrList in new strlis.c, to keep lists of strings (e.g. directory search paths)
#
# Revision 1.1  2013/12/25 14:39:51  pauloscustodio
# Move strutil.c to the z80asm/lib directory
#
# Revision 1.14  2013/12/15 13:18:35  pauloscustodio
# Move memory allocation routines to lib/xmalloc, instead of glib,
# introduce memory leak report on exit and memory fence check.
#
# Revision 1.13  2013/09/24 00:05:36  pauloscustodio
#
# Revision 1.12  2013/09/23 23:14:10  pauloscustodio
# Renamed SzList to StringList, simplified interface by assuming that
# list lives in memory util program ends; it is used for directory searches
# only. Moved interface to strutil.c, removed strlist.c.
#
# Revision 1.11  2013/09/09 00:20:45  pauloscustodio
# Add default set of modules to t_compile_module:
# -DMEMALLOC_DEBUG xmalloc.c die.o except.o strpool.o
#
# Revision 1.10  2013/04/29 22:24:33  pauloscustodio
# Add utility functions to convert end-of-line sequences CR, CRLF, LFCR, LF all to LF
#
# Revision 1.9  2013/02/22 17:21:29  pauloscustodio
# Added chomp()
#
# Revision 1.8  2013/01/20 21:24:29  pauloscustodio
# Updated copyright year to 2013
#
# Revision 1.7  2012/06/14 15:01:27  pauloscustodio
# Split safe strings from strutil.c to safestr.c
#
# Revision 1.6  2012/06/07 11:49:59  pauloscustodio
# stricompare() instead of Flncmp()
#
# Revision 1.5  2012/06/06 22:42:57  pauloscustodio
# BUG_0021 : Different behaviour in string truncation in strutil in Linux and Win32
#
# Revision 1.4  2012/05/26 18:50:26  pauloscustodio
# Use .o instead of .c to build test program, faster compilation.
# Use gcc to compile instead of cc.
#
# Revision 1.3  2012/05/26 17:46:01  pauloscustodio
# Put back strtoupper, strupr does not exist in all systems, was causing nightly build to fail
#
# Revision 1.2  2012/05/24 15:07:03  pauloscustodio
# Rename safestr_t to sstr_t, keep length to speed-up appending chars
#
# Revision 1.1  2012/05/22 20:26:17  pauloscustodio
# Safe strings
# New type sstr_t to hold strings with size to prevent buffer overruns.
# Remove strtoupper, use POSIX strupr instead
#
