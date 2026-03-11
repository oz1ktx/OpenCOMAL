/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"

#define YYDEBUG 1

/*
 * OpenComal -- a free Comal implementation
 *
 * This file is part of the OpenComal package.
 * (c) Copyright 1992-2002 Jos Visser <josv@osp.nl>
 *
 * The OpenComal package is covered by the GNU General Public
 * License. See doc/LICENSE for more information.
 */


/* The OpenComal parser */

#define PDCPARS

#include "comal_base.h"
#include "parser_support.h"
#include "comal_misc.h"
#include "comal_id.h"
#include "comal_program.h"

#include <string.h>

#define yyunion(x,y)	( (*(x)) = (*(y)) )

PUBLIC struct comal_line c_line;

PRIVATE void p_error(const char *msg);

extern int yylex();
extern int exp_list_of_nums(struct exp_list *root);
extern char *exp_cmd(struct expression *exp);
extern struct comal_line *stat_dup(struct comal_line *stat);

#define PARS_ALLOC(type) static_cast<type *>(mem_alloc(PARSE_POOL, sizeof(type)))
#define PARS_REVERSE(type, root) static_cast<type *>(my_reverse(root))


#line 113 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_andSYM = 3,                     /* andSYM  */
  YYSYMBOL_andthenSYM = 4,                 /* andthenSYM  */
  YYSYMBOL_appendSYM = 5,                  /* appendSYM  */
  YYSYMBOL_autoSYM = 6,                    /* autoSYM  */
  YYSYMBOL_becomesSYM = 7,                 /* becomesSYM  */
  YYSYMBOL_becplusSYM = 8,                 /* becplusSYM  */
  YYSYMBOL_becminusSYM = 9,                /* becminusSYM  */
  YYSYMBOL_caseSYM = 10,                   /* caseSYM  */
  YYSYMBOL_chdirSYM = 11,                  /* chdirSYM  */
  YYSYMBOL_closedSYM = 12,                 /* closedSYM  */
  YYSYMBOL_closeSYM = 13,                  /* closeSYM  */
  YYSYMBOL_colonSYM = 14,                  /* colonSYM  */
  YYSYMBOL_commaSYM = 15,                  /* commaSYM  */
  YYSYMBOL_contSYM = 16,                   /* contSYM  */
  YYSYMBOL_cursorSYM = 17,                 /* cursorSYM  */
  YYSYMBOL_dataSYM = 18,                   /* dataSYM  */
  YYSYMBOL_delSYM = 19,                    /* delSYM  */
  YYSYMBOL_dimSYM = 20,                    /* dimSYM  */
  YYSYMBOL_dirSYM = 21,                    /* dirSYM  */
  YYSYMBOL_drawSYM = 22,                   /* drawSYM  */
  YYSYMBOL_divideSYM = 23,                 /* divideSYM  */
  YYSYMBOL_divSYM = 24,                    /* divSYM  */
  YYSYMBOL_doSYM = 25,                     /* doSYM  */
  YYSYMBOL_downtoSYM = 26,                 /* downtoSYM  */
  YYSYMBOL_dynamicSYM = 27,                /* dynamicSYM  */
  YYSYMBOL_editSYM = 28,                   /* editSYM  */
  YYSYMBOL_elifSYM = 29,                   /* elifSYM  */
  YYSYMBOL_elseSYM = 30,                   /* elseSYM  */
  YYSYMBOL_endcaseSYM = 31,                /* endcaseSYM  */
  YYSYMBOL_endforSYM = 32,                 /* endforSYM  */
  YYSYMBOL_endfuncSYM = 33,                /* endfuncSYM  */
  YYSYMBOL_endifSYM = 34,                  /* endifSYM  */
  YYSYMBOL_endloopSYM = 35,                /* endloopSYM  */
  YYSYMBOL_endprocSYM = 36,                /* endprocSYM  */
  YYSYMBOL_endSYM = 37,                    /* endSYM  */
  YYSYMBOL_endtrapSYM = 38,                /* endtrapSYM  */
  YYSYMBOL_endwhileSYM = 39,               /* endwhileSYM  */
  YYSYMBOL_envSYM = 40,                    /* envSYM  */
  YYSYMBOL_enterSYM = 41,                  /* enterSYM  */
  YYSYMBOL_eolnSYM = 42,                   /* eolnSYM  */
  YYSYMBOL_eorSYM = 43,                    /* eorSYM  */
  YYSYMBOL_eqlSYM = 44,                    /* eqlSYM  */
  YYSYMBOL_escSYM = 45,                    /* escSYM  */
  YYSYMBOL_execSYM = 46,                   /* execSYM  */
  YYSYMBOL_exitSYM = 47,                   /* exitSYM  */
  YYSYMBOL_externalSYM = 48,               /* externalSYM  */
  YYSYMBOL_fileSYM = 49,                   /* fileSYM  */
  YYSYMBOL_forSYM = 50,                    /* forSYM  */
  YYSYMBOL_funcSYM = 51,                   /* funcSYM  */
  YYSYMBOL_geqSYM = 52,                    /* geqSYM  */
  YYSYMBOL_gtrSYM = 53,                    /* gtrSYM  */
  YYSYMBOL_handlerSYM = 54,                /* handlerSYM  */
  YYSYMBOL_ifSYM = 55,                     /* ifSYM  */
  YYSYMBOL_importSYM = 56,                 /* importSYM  */
  YYSYMBOL_inputSYM = 57,                  /* inputSYM  */
  YYSYMBOL_inSYM = 58,                     /* inSYM  */
  YYSYMBOL_leqSYM = 59,                    /* leqSYM  */
  YYSYMBOL_listSYM = 60,                   /* listSYM  */
  YYSYMBOL_localSYM = 61,                  /* localSYM  */
  YYSYMBOL_loadSYM = 62,                   /* loadSYM  */
  YYSYMBOL_loopSYM = 63,                   /* loopSYM  */
  YYSYMBOL_lparenSYM = 64,                 /* lparenSYM  */
  YYSYMBOL_lssSYM = 65,                    /* lssSYM  */
  YYSYMBOL_minusSYM = 66,                  /* minusSYM  */
  YYSYMBOL_mkdirSYM = 67,                  /* mkdirSYM  */
  YYSYMBOL_modSYM = 68,                    /* modSYM  */
  YYSYMBOL_nameSYM = 69,                   /* nameSYM  */
  YYSYMBOL_neqSYM = 70,                    /* neqSYM  */
  YYSYMBOL_newSYM = 71,                    /* newSYM  */
  YYSYMBOL_nullSYM = 72,                   /* nullSYM  */
  YYSYMBOL_ofSYM = 73,                     /* ofSYM  */
  YYSYMBOL_openSYM = 74,                   /* openSYM  */
  YYSYMBOL_orSYM = 75,                     /* orSYM  */
  YYSYMBOL_orthenSYM = 76,                 /* orthenSYM  */
  YYSYMBOL_osSYM = 77,                     /* osSYM  */
  YYSYMBOL_otherwiseSYM = 78,              /* otherwiseSYM  */
  YYSYMBOL_pageSYM = 79,                   /* pageSYM  */
  YYSYMBOL_plusSYM = 80,                   /* plusSYM  */
  YYSYMBOL_powerSYM = 81,                  /* powerSYM  */
  YYSYMBOL_printSYM = 82,                  /* printSYM  */
  YYSYMBOL_procSYM = 83,                   /* procSYM  */
  YYSYMBOL_quitSYM = 84,                   /* quitSYM  */
  YYSYMBOL_randomSYM = 85,                 /* randomSYM  */
  YYSYMBOL_readSYM = 86,                   /* readSYM  */
  YYSYMBOL_read_onlySYM = 87,              /* read_onlySYM  */
  YYSYMBOL_refSYM = 88,                    /* refSYM  */
  YYSYMBOL_renumberSYM = 89,               /* renumberSYM  */
  YYSYMBOL_repeatSYM = 90,                 /* repeatSYM  */
  YYSYMBOL_restoreSYM = 91,                /* restoreSYM  */
  YYSYMBOL_retrySYM = 92,                  /* retrySYM  */
  YYSYMBOL_returnSYM = 93,                 /* returnSYM  */
  YYSYMBOL_rmdirSYM = 94,                  /* rmdirSYM  */
  YYSYMBOL_rndSYM = 95,                    /* rndSYM  */
  YYSYMBOL_rparenSYM = 96,                 /* rparenSYM  */
  YYSYMBOL_runSYM = 97,                    /* runSYM  */
  YYSYMBOL_saveSYM = 98,                   /* saveSYM  */
  YYSYMBOL_scanSYM = 99,                   /* scanSYM  */
  YYSYMBOL_select_inputSYM = 100,          /* select_inputSYM  */
  YYSYMBOL_select_outputSYM = 101,         /* select_outputSYM  */
  YYSYMBOL_semicolonSYM = 102,             /* semicolonSYM  */
  YYSYMBOL_staticSYM = 103,                /* staticSYM  */
  YYSYMBOL_stepSYM = 104,                  /* stepSYM  */
  YYSYMBOL_stopSYM = 105,                  /* stopSYM  */
  YYSYMBOL_sysSYM = 106,                   /* sysSYM  */
  YYSYMBOL_syssSYM = 107,                  /* syssSYM  */
  YYSYMBOL_thenSYM = 108,                  /* thenSYM  */
  YYSYMBOL_timesSYM = 109,                 /* timesSYM  */
  YYSYMBOL_toSYM = 110,                    /* toSYM  */
  YYSYMBOL_traceSYM = 111,                 /* traceSYM  */
  YYSYMBOL_trapSYM = 112,                  /* trapSYM  */
  YYSYMBOL_unitSYM = 113,                  /* unitSYM  */
  YYSYMBOL_untilSYM = 114,                 /* untilSYM  */
  YYSYMBOL_usingSYM = 115,                 /* usingSYM  */
  YYSYMBOL_whenSYM = 116,                  /* whenSYM  */
  YYSYMBOL_whileSYM = 117,                 /* whileSYM  */
  YYSYMBOL_writeSYM = 118,                 /* writeSYM  */
  YYSYMBOL_rnSYM = 119,                    /* rnSYM  */
  YYSYMBOL_rsSYM = 120,                    /* rsSYM  */
  YYSYMBOL_tnrnSYM = 121,                  /* tnrnSYM  */
  YYSYMBOL_tnrsSYM = 122,                  /* tnrsSYM  */
  YYSYMBOL_tsrnSYM = 123,                  /* tsrnSYM  */
  YYSYMBOL_tonrsSYM = 124,                 /* tonrsSYM  */
  YYSYMBOL_tsrsSYM = 125,                  /* tsrsSYM  */
  YYSYMBOL_tsrsnSYM = 126,                 /* tsrsnSYM  */
  YYSYMBOL_lenSYM = 127,                   /* lenSYM  */
  YYSYMBOL_floatnumSYM = 128,              /* floatnumSYM  */
  YYSYMBOL_idSYM = 129,                    /* idSYM  */
  YYSYMBOL_intidSYM = 130,                 /* intidSYM  */
  YYSYMBOL_stringidSYM = 131,              /* stringidSYM  */
  YYSYMBOL_intnumSYM = 132,                /* intnumSYM  */
  YYSYMBOL_remSYM = 133,                   /* remSYM  */
  YYSYMBOL_stringSYM = 134,                /* stringSYM  */
  YYSYMBOL_USIGN = 135,                    /* USIGN  */
  YYSYMBOL_YYACCEPT = 136,                 /* $accept  */
  YYSYMBOL_a_comal_line = 137,             /* a_comal_line  */
  YYSYMBOL_comal_line = 138,               /* comal_line  */
  YYSYMBOL_optrem = 139,                   /* optrem  */
  YYSYMBOL_command = 140,                  /* command  */
  YYSYMBOL_list_cmd = 141,                 /* list_cmd  */
  YYSYMBOL_line_range = 142,               /* line_range  */
  YYSYMBOL_renumlines = 143,               /* renumlines  */
  YYSYMBOL_autolines = 144,                /* autolines  */
  YYSYMBOL_program_line = 145,             /* program_line  */
  YYSYMBOL_complex_stat = 146,             /* complex_stat  */
  YYSYMBOL_simple_stat = 147,              /* simple_stat  */
  YYSYMBOL_complex_1word = 148,            /* complex_1word  */
  YYSYMBOL_simple_1word = 149,             /* simple_1word  */
  YYSYMBOL_case_stat = 150,                /* case_stat  */
  YYSYMBOL_close_stat = 151,               /* close_stat  */
  YYSYMBOL_cursor_stat = 152,              /* cursor_stat  */
  YYSYMBOL_chdir_stat = 153,               /* chdir_stat  */
  YYSYMBOL_rmdir_stat = 154,               /* rmdir_stat  */
  YYSYMBOL_mkdir_stat = 155,               /* mkdir_stat  */
  YYSYMBOL_data_stat = 156,                /* data_stat  */
  YYSYMBOL_draw_stat = 157,                /* draw_stat  */
  YYSYMBOL_del_stat = 158,                 /* del_stat  */
  YYSYMBOL_dir_stat = 159,                 /* dir_stat  */
  YYSYMBOL_unit_stat = 160,                /* unit_stat  */
  YYSYMBOL_local_stat = 161,               /* local_stat  */
  YYSYMBOL_local_list = 162,               /* local_list  */
  YYSYMBOL_local_item = 163,               /* local_item  */
  YYSYMBOL_dim_stat = 164,                 /* dim_stat  */
  YYSYMBOL_dim_list = 165,                 /* dim_list  */
  YYSYMBOL_dim_item = 166,                 /* dim_item  */
  YYSYMBOL_of = 167,                       /* of  */
  YYSYMBOL_opt_dim_ensions = 168,          /* opt_dim_ensions  */
  YYSYMBOL_dim_ensions = 169,              /* dim_ensions  */
  YYSYMBOL_dim_ension_list = 170,          /* dim_ension_list  */
  YYSYMBOL_dim_ension = 171,               /* dim_ension  */
  YYSYMBOL_elif_stat = 172,                /* elif_stat  */
  YYSYMBOL_exit_stat = 173,                /* exit_stat  */
  YYSYMBOL_ifwhen = 174,                   /* ifwhen  */
  YYSYMBOL_exec_stat = 175,                /* exec_stat  */
  YYSYMBOL_for_stat = 176,                 /* for_stat  */
  YYSYMBOL_todownto = 177,                 /* todownto  */
  YYSYMBOL_optstep = 178,                  /* optstep  */
  YYSYMBOL_func_stat = 179,                /* func_stat  */
  YYSYMBOL_if_stat = 180,                  /* if_stat  */
  YYSYMBOL_import_stat = 181,              /* import_stat  */
  YYSYMBOL_import_list = 182,              /* import_list  */
  YYSYMBOL_input_stat = 183,               /* input_stat  */
  YYSYMBOL_input_modifier = 184,           /* input_modifier  */
  YYSYMBOL_open_stat = 185,                /* open_stat  */
  YYSYMBOL_open_type = 186,                /* open_type  */
  YYSYMBOL_os_stat = 187,                  /* os_stat  */
  YYSYMBOL_print_stat = 188,               /* print_stat  */
  YYSYMBOL_printi = 189,                   /* printi  */
  YYSYMBOL_prnum_list = 190,               /* prnum_list  */
  YYSYMBOL_print_list = 191,               /* print_list  */
  YYSYMBOL_pr_sep = 192,                   /* pr_sep  */
  YYSYMBOL_optpr_sep = 193,                /* optpr_sep  */
  YYSYMBOL_proc_stat = 194,                /* proc_stat  */
  YYSYMBOL_read_stat = 195,                /* read_stat  */
  YYSYMBOL_restore_stat = 196,             /* restore_stat  */
  YYSYMBOL_return_stat = 197,              /* return_stat  */
  YYSYMBOL_run_stat = 198,                 /* run_stat  */
  YYSYMBOL_select_out_stat = 199,          /* select_out_stat  */
  YYSYMBOL_select_in_stat = 200,           /* select_in_stat  */
  YYSYMBOL_stop_stat = 201,                /* stop_stat  */
  YYSYMBOL_sys_stat = 202,                 /* sys_stat  */
  YYSYMBOL_until_stat = 203,               /* until_stat  */
  YYSYMBOL_trace_stat = 204,               /* trace_stat  */
  YYSYMBOL_trap_stat = 205,                /* trap_stat  */
  YYSYMBOL_plusorminus = 206,              /* plusorminus  */
  YYSYMBOL_when_stat = 207,                /* when_stat  */
  YYSYMBOL_when_list = 208,                /* when_list  */
  YYSYMBOL_when_numlist = 209,             /* when_numlist  */
  YYSYMBOL_when_numitem = 210,             /* when_numitem  */
  YYSYMBOL_when_strlist = 211,             /* when_strlist  */
  YYSYMBOL_when_stritem = 212,             /* when_stritem  */
  YYSYMBOL_relop = 213,                    /* relop  */
  YYSYMBOL_while_stat = 214,               /* while_stat  */
  YYSYMBOL_repeat_stat = 215,              /* repeat_stat  */
  YYSYMBOL_write_stat = 216,               /* write_stat  */
  YYSYMBOL_assign_stat = 217,              /* assign_stat  */
  YYSYMBOL_assign_list = 218,              /* assign_list  */
  YYSYMBOL_assign_item = 219,              /* assign_item  */
  YYSYMBOL_nassign = 220,                  /* nassign  */
  YYSYMBOL_sassign = 221,                  /* sassign  */
  YYSYMBOL_assign1 = 222,                  /* assign1  */
  YYSYMBOL_assign2 = 223,                  /* assign2  */
  YYSYMBOL_label_stat = 224,               /* label_stat  */
  YYSYMBOL_xid = 225,                      /* xid  */
  YYSYMBOL_exp = 226,                      /* exp  */
  YYSYMBOL_numexp = 227,                   /* numexp  */
  YYSYMBOL_numexp2 = 228,                  /* numexp2  */
  YYSYMBOL_stringexp = 229,                /* stringexp  */
  YYSYMBOL_stringexp2 = 230,               /* stringexp2  */
  YYSYMBOL_opt_stringexp = 231,            /* opt_stringexp  */
  YYSYMBOL_string_factor = 232,            /* string_factor  */
  YYSYMBOL_opt_arg = 233,                  /* opt_arg  */
  YYSYMBOL_substr_spec = 234,              /* substr_spec  */
  YYSYMBOL_substr_spec2 = 235,             /* substr_spec2  */
  YYSYMBOL_optnumlvalue = 236,             /* optnumlvalue  */
  YYSYMBOL_optexp = 237,                   /* optexp  */
  YYSYMBOL_optid = 238,                    /* optid  */
  YYSYMBOL_optid2 = 239,                   /* optid2  */
  YYSYMBOL_optfile = 240,                  /* optfile  */
  YYSYMBOL_optfileS = 241,                 /* optfileS  */
  YYSYMBOL_lval_list = 242,                /* lval_list  */
  YYSYMBOL_lvalue = 243,                   /* lvalue  */
  YYSYMBOL_numlvalue = 244,                /* numlvalue  */
  YYSYMBOL_numlvalue2 = 245,               /* numlvalue2  */
  YYSYMBOL_strlvalue = 246,                /* strlvalue  */
  YYSYMBOL_strlvalue2 = 247,               /* strlvalue2  */
  YYSYMBOL_file_designator = 248,          /* file_designator  */
  YYSYMBOL_opt_external = 249,             /* opt_external  */
  YYSYMBOL_procfunc_head = 250,            /* procfunc_head  */
  YYSYMBOL_parmlist = 251,                 /* parmlist  */
  YYSYMBOL_parmitem = 252,                 /* parmitem  */
  YYSYMBOL_oneparm = 253,                  /* oneparm  */
  YYSYMBOL_id = 254,                       /* id  */
  YYSYMBOL_numid = 255,                    /* numid  */
  YYSYMBOL_opt_commalist = 256,            /* opt_commalist  */
  YYSYMBOL_exp_list = 257,                 /* exp_list  */
  YYSYMBOL_optsimple_stat = 258,           /* optsimple_stat  */
  YYSYMBOL_optfilename = 259,              /* optfilename  */
  YYSYMBOL_optof = 260,                    /* optof  */
  YYSYMBOL_optdo = 261,                    /* optdo  */
  YYSYMBOL_optthen = 262,                  /* optthen  */
  YYSYMBOL_optread_only = 263,             /* optread_only  */
  YYSYMBOL_optclosed = 264                 /* optclosed  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  277
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1631

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  136
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  129
/* YYNRULES -- Number of rules.  */
#define YYNRULES  370
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  584

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   390


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   242,   242,   247,   256,   261,   269,   279,   289,   295,
     297,   303,   307,   308,   313,   318,   323,   328,   333,   337,
     341,   346,   350,   355,   360,   367,   374,   382,   389,   395,
     404,   407,   411,   415,   419,   425,   429,   433,   438,   443,
     447,   451,   457,   463,   464,   466,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   488,   489,   490,   491,   492,   493,   494,   495,   496,
     497,   498,   499,   500,   501,   502,   503,   504,   505,   506,
     507,   508,   509,   510,   511,   512,   513,   514,   515,   520,
     521,   524,   528,   532,   536,   540,   544,   548,   552,   556,
     560,   564,   570,   575,   579,   585,   589,   593,   598,   602,
     608,   615,   620,   627,   635,   642,   649,   656,   663,   685,
     692,   699,   707,   713,   718,   725,   729,   733,   737,   741,
     748,   755,   760,   767,   771,   775,   779,   785,   786,   789,
     791,   796,   802,   807,   814,   820,   826,   834,   841,   848,
     849,   852,   859,   871,   875,   881,   886,   891,   901,   909,
     915,   923,   930,   939,   947,   953,   960,   965,   974,   978,
     982,   986,   994,  1001,  1008,  1015,  1024,  1035,  1036,  1039,
    1043,  1049,  1053,  1059,  1063,  1069,  1071,  1076,  1086,  1094,
    1101,  1108,  1115,  1123,  1130,  1137,  1144,  1151,  1163,  1170,
    1174,  1180,  1187,  1188,  1191,  1196,  1199,  1203,  1209,  1214,
    1217,  1221,  1225,  1231,  1235,  1239,  1243,  1247,  1251,  1257,
    1265,  1273,  1281,  1288,  1293,  1299,  1303,  1309,  1310,  1313,
    1314,  1320,  1324,  1330,  1334,  1340,  1347,  1351,  1355,  1361,
    1362,  1365,  1371,  1375,  1379,  1383,  1387,  1391,  1395,  1399,
    1403,  1407,  1411,  1415,  1419,  1423,  1427,  1431,  1435,  1439,
    1443,  1447,  1451,  1455,  1459,  1463,  1467,  1471,  1475,  1479,
    1483,  1487,  1488,  1492,  1496,  1500,  1504,  1508,  1512,  1516,
    1520,  1524,  1530,  1536,  1540,  1541,  1547,  1549,  1554,  1555,
    1559,  1563,  1567,  1571,  1575,  1579,  1583,  1587,  1593,  1598,
    1603,  1609,  1614,  1619,  1624,  1631,  1633,  1638,  1640,  1645,
    1647,  1652,  1654,  1659,  1666,  1671,  1672,  1675,  1679,  1685,
    1686,  1689,  1696,  1697,  1701,  1705,  1711,  1718,  1722,  1726,
    1730,  1734,  1740,  1745,  1752,  1760,  1768,  1777,  1782,  1787,
    1792,  1797,  1804,  1811,  1818,  1825,  1832,  1841,  1846,  1853,
    1854,  1857,  1858,  1861,  1862,  1865,  1869,  1875,  1886,  1891,
    1893,  1898,  1899,  1902,  1903,  1906,  1907,  1910,  1915,  1920,
    1925
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "andSYM", "andthenSYM",
  "appendSYM", "autoSYM", "becomesSYM", "becplusSYM", "becminusSYM",
  "caseSYM", "chdirSYM", "closedSYM", "closeSYM", "colonSYM", "commaSYM",
  "contSYM", "cursorSYM", "dataSYM", "delSYM", "dimSYM", "dirSYM",
  "drawSYM", "divideSYM", "divSYM", "doSYM", "downtoSYM", "dynamicSYM",
  "editSYM", "elifSYM", "elseSYM", "endcaseSYM", "endforSYM", "endfuncSYM",
  "endifSYM", "endloopSYM", "endprocSYM", "endSYM", "endtrapSYM",
  "endwhileSYM", "envSYM", "enterSYM", "eolnSYM", "eorSYM", "eqlSYM",
  "escSYM", "execSYM", "exitSYM", "externalSYM", "fileSYM", "forSYM",
  "funcSYM", "geqSYM", "gtrSYM", "handlerSYM", "ifSYM", "importSYM",
  "inputSYM", "inSYM", "leqSYM", "listSYM", "localSYM", "loadSYM",
  "loopSYM", "lparenSYM", "lssSYM", "minusSYM", "mkdirSYM", "modSYM",
  "nameSYM", "neqSYM", "newSYM", "nullSYM", "ofSYM", "openSYM", "orSYM",
  "orthenSYM", "osSYM", "otherwiseSYM", "pageSYM", "plusSYM", "powerSYM",
  "printSYM", "procSYM", "quitSYM", "randomSYM", "readSYM", "read_onlySYM",
  "refSYM", "renumberSYM", "repeatSYM", "restoreSYM", "retrySYM",
  "returnSYM", "rmdirSYM", "rndSYM", "rparenSYM", "runSYM", "saveSYM",
  "scanSYM", "select_inputSYM", "select_outputSYM", "semicolonSYM",
  "staticSYM", "stepSYM", "stopSYM", "sysSYM", "syssSYM", "thenSYM",
  "timesSYM", "toSYM", "traceSYM", "trapSYM", "unitSYM", "untilSYM",
  "usingSYM", "whenSYM", "whileSYM", "writeSYM", "rnSYM", "rsSYM",
  "tnrnSYM", "tnrsSYM", "tsrnSYM", "tonrsSYM", "tsrsSYM", "tsrsnSYM",
  "lenSYM", "floatnumSYM", "idSYM", "intidSYM", "stringidSYM", "intnumSYM",
  "remSYM", "stringSYM", "USIGN", "$accept", "a_comal_line", "comal_line",
  "optrem", "command", "list_cmd", "line_range", "renumlines", "autolines",
  "program_line", "complex_stat", "simple_stat", "complex_1word",
  "simple_1word", "case_stat", "close_stat", "cursor_stat", "chdir_stat",
  "rmdir_stat", "mkdir_stat", "data_stat", "draw_stat", "del_stat",
  "dir_stat", "unit_stat", "local_stat", "local_list", "local_item",
  "dim_stat", "dim_list", "dim_item", "of", "opt_dim_ensions",
  "dim_ensions", "dim_ension_list", "dim_ension", "elif_stat", "exit_stat",
  "ifwhen", "exec_stat", "for_stat", "todownto", "optstep", "func_stat",
  "if_stat", "import_stat", "import_list", "input_stat", "input_modifier",
  "open_stat", "open_type", "os_stat", "print_stat", "printi",
  "prnum_list", "print_list", "pr_sep", "optpr_sep", "proc_stat",
  "read_stat", "restore_stat", "return_stat", "run_stat",
  "select_out_stat", "select_in_stat", "stop_stat", "sys_stat",
  "until_stat", "trace_stat", "trap_stat", "plusorminus", "when_stat",
  "when_list", "when_numlist", "when_numitem", "when_strlist",
  "when_stritem", "relop", "while_stat", "repeat_stat", "write_stat",
  "assign_stat", "assign_list", "assign_item", "nassign", "sassign",
  "assign1", "assign2", "label_stat", "xid", "exp", "numexp", "numexp2",
  "stringexp", "stringexp2", "opt_stringexp", "string_factor", "opt_arg",
  "substr_spec", "substr_spec2", "optnumlvalue", "optexp", "optid",
  "optid2", "optfile", "optfileS", "lval_list", "lvalue", "numlvalue",
  "numlvalue2", "strlvalue", "strlvalue2", "file_designator",
  "opt_external", "procfunc_head", "parmlist", "parmitem", "oneparm", "id",
  "numid", "opt_commalist", "exp_list", "optsimple_stat", "optfilename",
  "optof", "optdo", "optthen", "optread_only", "optclosed", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-404)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-112)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     668,    17,    -6,  1497,   327,    -3,  -404,  1497,  1497,   202,
     126,   327,  1497,    16,  1497,  -404,  -404,   -73,   166,  -404,
    -404,   -48,  -404,  -404,  -404,   -48,  -101,   -44,     5,   -73,
     166,  -404,  1497,   166,   -17,   101,   176,   -43,  -404,   327,
    -404,  -404,    69,   327,  -404,  -404,  -404,    25,  -404,    80,
       8,   909,   -48,  -404,  1497,   327,   327,   -43,  -404,   327,
     327,  -404,  1497,  1497,  1497,    87,   327,  1497,  1332,  1497,
      80,    28,   102,   114,   794,  -404,   182,   148,  -404,  -404,
    -404,    78,    78,  -404,  -404,  -404,  -404,  -404,  -404,  -404,
    -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,
    -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,  1459,
    -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,
    -404,  -404,  -404,  -404,  -404,  -404,  -404,   121,  -404,  -404,
     -24,   232,  -404,   178,  -404,  -404,    84,   219,  -404,  1497,
    1497,  1497,   180,   184,   186,  -404,  -404,   197,   203,   209,
     224,   234,   238,   247,  -404,   248,  -404,  -404,  -404,   185,
    -404,  1313,  -404,   300,   251,  -404,  -404,   327,  -404,   -45,
    -404,  1497,   301,   300,  -404,   314,   199,   266,  -404,  -404,
    -404,  -404,   104,   320,  -404,   273,  -404,  -404,   314,  -404,
     231,  -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,
    -404,  -404,  -404,  -404,  1497,    42,   276,   231,   328,  -404,
      31,  1497,   332,   189,  -404,  -404,   333,   336,   181,   341,
    -404,   273,  -404,  -404,  -404,  1497,  -404,   276,   189,  -404,
     210,   345,  -404,   327,  -404,   327,    87,   233,  -404,  -404,
    -404,  -404,  -404,  -404,  -404,  -404,  -404,   314,  -404,    18,
    -404,  -404,  -404,  -404,  -404,   327,  -404,  -404,  -404,  -404,
     348,  -404,   352,  -404,  1497,  -404,  -404,   344,  1497,  -404,
    1497,  1497,   468,  -404,    78,  -404,  -404,  -404,  -404,  -404,
    -404,   327,    21,  -404,  1497,   189,  -404,  -404,  -404,  -404,
    1497,  -404,  -404,  -404,   327,  -404,  -404,   239,   989,   448,
    -404,  -404,  1497,  1497,  1497,  1497,  1497,   327,  1497,  -404,
     327,  1497,  1497,  -404,  -404,  1497,  1497,  1497,  1497,  1497,
    1497,  1497,  1497,  1497,  1497,  1497,  1497,  1497,  1497,  1497,
    1497,  1497,  1497,   327,   327,   327,   327,   327,   327,   327,
     327,  1497,   468,  -404,   156,   314,  1497,  1497,  -404,   241,
    1497,  1497,    24,   126,  -404,  -404,  -404,  -404,  1497,    96,
     362,   909,   166,   166,  -404,    74,  -404,   360,  -404,  -404,
    -404,   242,   244,  1497,    24,   176,  -404,  -404,   364,   362,
     360,  -404,   249,  1497,  -404,  -404,  -404,  -404,  1421,    49,
    -404,  -404,  -404,   909,   314,    26,    29,    32,    35,  1497,
     369,   288,    43,    47,  -404,   371,  -404,  -404,  1497,  -404,
      21,  -404,  -404,  -404,  -404,  -404,  -404,   194,    55,    56,
    1043,  1097,   214,  1151,   221,    57,  1205,   889,  1424,  1424,
     305,   305,  1424,   140,   140,   140,   140,   140,   134,   305,
     140,  1424,  1424,   134,   305,   305,   -45,   -45,   -45,  -404,
     -45,   -45,   -45,   251,   305,   369,  -404,  -404,  -404,    63,
    -404,   191,  -404,  -404,  -404,  1497,  -404,    14,   166,   166,
     260,   166,    64,  -404,  -404,   326,  -404,    67,  -404,  -404,
    -404,   328,    65,  -404,  1497,   189,  -404,  -404,  -404,  1497,
    -404,   327,    67,  -404,  -404,  -404,  1497,  -404,   327,  -404,
    -404,  -404,  -404,  -404,  -404,   378,  1497,  -404,  -404,   251,
    1497,  -404,  1497,  1497,  -404,  -404,  -404,  -404,  -404,  -404,
    -404,  -404,  -404,  -404,  -404,  1497,  -404,  1497,  1497,  -404,
    -404,  -404,  1497,  -404,  -404,  -404,  -404,    96,  -404,   347,
     327,   351,  -404,  -404,   386,  -404,  -404,   387,  -404,  -404,
    -404,  -404,    21,  -404,  1259,  -404,  -404,  -404,   302,  -404,
     327,  -404,   327,  -404,    20,  1497,  -404,  -404,  1497,   344,
    -404,  -404,  -404,  1497,  -404,  -404,  -404,  -404,  -404,   909,
     321,  -404,  -404,  -404
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,     0,    42,     0,     0,   316,    21,     0,     0,    30,
       0,   287,     0,    30,     0,    91,    92,   306,   310,    94,
      96,   312,   106,   104,    98,   312,     0,     0,   107,     0,
       0,   103,     0,     0,   166,    30,     0,   360,    95,     0,
      18,   105,     0,     0,   100,   108,   177,     0,    11,   314,
      38,   101,   312,   109,   308,     0,    17,   360,    19,     0,
       0,   178,   308,     0,     0,   102,     0,     0,     0,     0,
       0,   236,   323,   327,    45,     9,     0,     0,     8,     4,
      12,    10,    10,    60,    90,    46,    61,    63,    62,    78,
      71,    47,    48,    64,    66,    86,    67,    65,    49,    50,
      68,    51,    52,    53,    69,    70,    72,    73,    74,   173,
      54,    75,    76,    77,    79,    80,    81,    82,    83,    55,
      84,    85,    56,    57,    58,    87,    89,   222,   224,    59,
     322,     0,   321,     0,   326,     3,     0,    39,    20,     0,
       0,     0,   276,     0,     0,   279,   292,     0,     0,     0,
     299,     0,     0,     0,   270,   236,   269,   294,   322,   362,
     239,   241,   240,   282,   284,   271,   288,     0,   114,   282,
     315,     0,     0,     0,   356,   117,     0,    31,    22,   119,
     351,   352,     0,   130,   132,     0,   286,   120,   118,    23,
     366,    99,   305,   350,    93,   309,   349,   311,    97,    16,
      15,   151,   149,   150,     0,     0,   339,   366,   160,   162,
     347,     0,     0,     0,   164,    26,    25,    28,   126,   122,
     124,   140,   359,    14,   116,     0,   172,   339,     0,   313,
       0,    35,    24,     0,   107,     0,     0,     0,   189,   307,
     190,   115,   191,    13,   193,   192,   194,   195,   197,     0,
     121,   196,   215,   217,   213,     0,   218,   214,   216,   201,
     202,   205,   203,   209,     0,   207,   211,   364,     0,   235,
     354,   354,   354,   329,    10,    43,    44,     1,     2,     6,
       7,     0,   186,   182,     0,     0,   232,   233,   234,   231,
       0,   227,   228,   230,     0,   229,    41,     0,     0,     0,
     267,   268,     0,     0,     0,     0,     0,     0,     0,   293,
       0,     0,     0,   361,   110,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   289,     0,   112,     0,     0,    32,    33,
       0,     0,   136,     0,   133,   365,   147,   148,     0,     0,
     370,   358,     0,     0,   354,     0,   165,   163,   318,   319,
     320,     0,     0,     0,   129,     0,   125,   139,     0,   370,
     188,    37,     0,     0,   200,   199,   198,   212,     0,     0,
     206,   210,   363,   358,   221,     0,     0,     0,     0,     0,
     239,     0,     0,     0,     5,     0,   183,   184,   185,   174,
     176,   223,   225,   226,    40,   281,   297,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   248,   249,
     256,   258,   252,   242,   247,   245,   246,   244,   254,   259,
     243,   250,   251,   253,   257,   255,   260,   265,   263,   266,
     264,   262,   261,   283,   285,     0,   113,   355,    34,     0,
     143,   144,   134,   137,   138,     0,   131,     0,     0,     0,
       0,     0,     0,   341,   342,   347,   369,   337,   357,   158,
     161,   159,     0,   332,     0,     0,    27,    29,   127,     0,
     123,     0,   337,    36,   220,   204,     0,   208,     0,   219,
     353,   238,   237,   325,   324,   302,   303,   300,   331,   328,
       0,   181,     0,     0,   277,   280,   295,   275,   290,   272,
     298,   291,   296,   274,   273,     0,   141,     0,     0,   135,
     154,   153,     0,   346,   344,   345,   343,     0,   338,     0,
       0,     0,   157,   348,     0,   317,   128,     0,   187,   304,
     301,   330,   186,   180,     0,   142,   146,   145,   156,   340,
       0,   334,     0,   333,     0,   185,   175,   278,     0,   364,
     335,   336,   170,     0,   168,   169,   167,   179,   155,   358,
     368,   152,   367,   171
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -404,  -404,  -404,   -67,  -404,  -404,    30,  -404,  -404,  -404,
     337,    76,  -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,
    -404,  -404,  -404,  -404,  -404,  -404,  -404,    37,  -404,  -404,
      54,    36,  -404,    66,  -404,  -112,  -404,  -404,  -404,  -404,
    -404,  -404,  -404,  -404,  -404,  -404,    53,  -404,  -404,  -404,
    -404,  -404,  -404,  -404,  -404,   135,  -403,  -134,  -404,  -404,
    -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,
    -404,  -404,  -404,  -404,    33,  -404,    34,   -96,  -404,  -404,
    -404,  -404,  -404,   137,  -404,  -404,  -109,  -404,  -404,     3,
       7,    -1,   334,    44,   133,  -404,    86,  -404,   -71,  -404,
    -404,   358,  -404,   110,  -404,  -404,   196,   -60,    -9,     0,
    -202,     1,    85,   -64,   204,  -404,  -108,  -325,   -14,     2,
    -244,    10,  -388,   373,  -404,  -137,   228,  -404,    60
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    76,    77,    78,    79,    80,   178,   232,   138,   274,
      81,   478,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,   219,   220,    97,   183,
     184,   465,   376,   352,   459,   460,    98,    99,   204,   100,
     101,   532,   569,   102,   103,   104,   208,   105,   213,   106,
     576,   107,   108,   109,   552,   282,   408,   409,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     386,   122,   259,   260,   261,   262,   263,   264,   123,   124,
     125,   126,   127,   128,   290,   294,   291,   292,   129,   158,
     174,   160,   161,   162,   173,   187,   164,   309,   343,   401,
     191,   240,   194,   198,   228,   171,   367,   368,   131,   165,
     133,   166,   214,   542,   360,   472,   473,   209,   475,   196,
     395,   175,   479,   223,   314,   393,   356,   583,   477
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     132,   134,   273,   130,   195,   499,   172,   512,   192,   136,
     159,   370,   185,   190,   279,   280,   206,   132,   -88,   210,
     205,   217,   188,   230,   295,   572,   370,   397,   402,   132,
     201,   207,   211,   200,   474,   340,   406,   480,   221,  -111,
     530,   500,   269,   189,   347,   363,   170,   500,   168,   286,
     347,   132,   134,   179,   130,   186,   155,    72,   500,   135,
     202,   239,   347,   248,   341,   216,   251,   265,   267,   239,
     347,   347,   347,   247,   132,   134,    82,   130,   525,   537,
     500,   197,   176,   224,   384,   155,   289,   226,   483,   484,
     -88,   222,   270,   252,   539,   364,   358,   463,   385,   241,
     242,   253,   254,   244,   245,   573,   574,   255,   256,   -88,
     250,  -111,   266,   167,   257,   540,   283,   212,   225,   258,
     482,   203,   501,   407,   531,   502,   137,   237,   503,   211,
    -111,   504,   249,   464,   229,   199,   163,   169,   575,   508,
     231,   163,   169,   509,   169,   163,   536,   468,   177,   565,
     276,   515,   516,   522,   227,   268,   144,   317,   318,   526,
     538,   543,   238,   317,   318,   469,   271,   176,   350,   146,
     541,   148,   169,   150,   151,   152,   169,   351,   272,   470,
      73,   345,   277,   157,   471,   286,   293,   163,   169,   169,
     278,   581,   169,   169,   284,   163,   163,   315,   316,   169,
     527,   163,   326,   357,   369,   528,   325,   404,   326,   513,
     365,    75,   474,   132,   134,   331,   296,   317,   318,   369,
     330,   331,   289,   285,   378,   180,   181,   193,   132,   134,
     180,   181,   193,   177,   297,   215,   340,   319,   320,   286,
     287,   288,   163,   332,   302,   350,   321,   322,   303,   332,
     304,   354,   416,   323,   373,   180,   181,   182,   313,   324,
     325,   305,   326,   390,   327,   341,   167,   306,   176,   328,
     329,   400,   299,   307,   330,   331,   289,   179,   394,   242,
     396,   398,   403,   370,   374,   132,   134,   377,   308,   412,
     514,   283,   496,   498,   340,   180,   181,   193,   310,   387,
     344,   340,   311,   332,   163,   180,   181,   218,   391,   144,
     519,   312,   270,   418,   419,   342,   346,   521,   155,    72,
      73,   425,   146,   341,   148,   405,   150,   151,   152,   347,
     341,   348,   349,    73,   177,   353,   157,   350,   413,   355,
     359,   455,   381,   362,   333,   456,   366,   383,   371,   461,
     462,   372,   334,   335,   457,   185,   375,   467,   336,   337,
     382,   132,   134,   388,   130,   338,   169,   389,   169,   392,
     339,   414,   488,   458,   476,   485,   486,   221,   487,   491,
     340,   493,   494,   506,   507,   510,   331,   265,   169,   535,
     364,   167,   549,   132,   134,   560,   130,   163,   505,   562,
     563,   163,   564,   163,   163,   163,   568,   466,   582,   341,
     489,   275,   490,   555,   169,   511,   481,   163,   566,   410,
     246,   495,   411,   497,   380,   545,   453,   169,   548,   559,
     243,   379,   579,   266,   144,   361,   163,   163,   551,   492,
     422,     0,     0,   424,   163,   427,     0,   146,     0,   148,
       0,   150,   151,   152,   533,   534,     0,     0,    73,     0,
       0,   157,     0,     0,   529,     0,   446,   447,   448,   449,
     450,   451,   452,   298,   300,   301,   369,     0,     0,     0,
     163,     0,   399,   544,     0,   132,   134,     0,   546,     0,
       0,     0,   333,     0,     0,   390,     0,     0,     0,     0,
     334,   335,     0,     0,     0,   550,   336,   337,     0,   553,
       0,     0,     0,   338,     0,     0,     0,     0,   339,   511,
       0,     0,   169,     0,   461,     0,   556,   557,   340,     0,
       0,   558,   139,     0,   140,   547,     0,     0,     0,     0,
       0,   163,   391,     0,   416,     0,     0,     0,   141,     0,
       0,     0,     0,     0,     0,     0,     0,   341,     0,     0,
       0,     0,     0,   142,   577,     0,     0,   578,     0,     0,
       0,     0,   580,     0,   143,   144,     0,     0,     0,   132,
     134,     0,   130,     0,   561,     0,     0,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,    72,    73,
     156,     0,   157,     0,   570,     0,   571,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   169,     0,     0,     0,     0,     0,
       0,   169,     0,     0,     0,     0,   417,     0,     0,   420,
     421,     0,   423,     0,     0,   163,   426,     0,     0,   428,
     429,   430,   431,   432,   433,   434,   435,   436,   437,   438,
     439,   440,   441,   442,   443,   444,   445,     0,     0,     1,
       0,     0,     0,   169,     2,   454,     0,     0,     3,     4,
       0,     5,     0,     0,     6,     7,     8,     9,    10,    11,
      12,     0,     0,   169,     0,   169,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
     -10,     0,     0,     0,    27,    28,     0,     0,    29,    30,
       0,     0,    31,    32,    33,    34,     0,     0,    35,    36,
      37,    38,     0,     0,     0,    39,     0,     0,     0,    40,
      41,     0,    42,     0,     0,    43,    44,    45,     0,     0,
      46,    47,    48,     0,    49,     0,     0,    50,    51,    52,
      53,    54,    55,     0,     0,    56,    57,    58,    59,    60,
      61,     0,     0,    62,    63,     0,     0,     0,     0,    64,
      65,    66,    67,     0,    68,    69,    70,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    71,    72,    73,
      74,    75,     0,     0,     3,     4,     0,     5,     0,     0,
       0,     7,     8,   233,    10,    11,    12,     0,     0,     0,
       0,     0,     0,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,     0,     0,     0,     0,     0,     0,
      27,    28,     0,     0,    29,    30,     0,   554,    31,    32,
      33,    34,     0,     0,     0,    36,     0,    38,     0,     0,
       0,    39,     0,     0,     0,     0,    41,     0,    42,     0,
       0,    43,    44,    45,     0,     0,    46,    47,     0,     0,
      49,     0,     0,     0,    51,    52,    53,    54,    55,     0,
       0,   235,     0,     0,    59,    60,    61,     0,     0,    62,
      63,     0,     0,     0,     0,    64,    65,    66,    67,     0,
      68,    69,    70,     0,     0,     0,     0,     0,     0,     0,
       4,     0,     5,    71,    72,    73,     7,     0,   233,    10,
      11,     0,     0,   333,     0,     0,     0,     0,     0,     0,
       0,   334,   335,     0,     0,     0,    22,   336,   337,     0,
       0,     0,     0,     0,   338,    27,   234,     0,     0,   339,
       0,     0,     0,     0,     0,    33,    34,     0,     0,   340,
      36,     0,     0,     0,     0,     0,    39,     0,     0,     0,
       0,    41,     0,    42,     0,   524,    43,     0,    45,     0,
       0,    46,   315,   316,     0,    49,     0,     0,   341,     0,
      52,    53,    54,    55,     0,     0,   235,     0,     0,    59,
      60,    61,   317,   318,    62,    63,     0,     0,     0,     0,
      64,   236,    66,     0,     0,     0,     0,    70,     0,     0,
       0,     0,   319,   320,     0,     0,     0,     0,   155,    72,
      73,   321,   322,     0,     0,     0,   315,   316,   323,     0,
       0,     0,     0,     0,   324,   325,     0,   326,     0,   327,
       0,     0,     0,     0,   328,   329,   317,   318,     0,   330,
     331,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   415,   319,   320,     0,     0,
       0,     0,     0,     0,     0,   321,   322,     0,   332,     0,
     315,   316,   323,     0,     0,     0,     0,     0,   324,   325,
       0,   326,     0,   327,     0,     0,     0,     0,   328,   329,
     317,   318,     0,   330,   331,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   517,
     319,   320,     0,     0,     0,     0,     0,     0,     0,   321,
     322,     0,   332,     0,   315,   316,   323,     0,     0,     0,
       0,     0,   324,   325,     0,   326,     0,   327,     0,     0,
       0,     0,   328,   329,   317,   318,     0,   330,   331,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   518,   319,   320,     0,     0,     0,     0,
       0,     0,     0,   321,   322,     0,   332,     0,   315,   316,
     323,     0,     0,     0,     0,     0,   324,   325,     0,   326,
       0,   327,     0,     0,     0,     0,   328,   329,   317,   318,
       0,   330,   331,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   520,   319,   320,
       0,     0,     0,     0,     0,     0,     0,   321,   322,     0,
     332,     0,   315,   316,   323,     0,     0,     0,     0,     0,
     324,   325,     0,   326,     0,   327,     0,     0,     0,     0,
     328,   329,   317,   318,     0,   330,   331,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   523,   319,   320,     0,     0,     0,     0,     0,     0,
       0,   321,   322,     0,   332,     0,   315,   316,   323,     0,
       0,     0,     0,     0,   324,   325,     0,   326,     0,   327,
       0,     0,     0,     0,   328,   329,   317,   318,     0,   330,
     331,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   567,   319,   320,     0,     0,
       0,     0,     0,     0,     0,   321,   322,     0,   332,     0,
       0,     0,   323,     0,     0,     0,   252,     0,   324,   325,
       0,   326,     0,   327,   253,   254,     0,     0,   328,   329,
     255,   256,     0,   330,   331,     0,   139,   257,   140,     0,
       0,     0,   258,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   141,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   332,     0,     0,     0,     0,   142,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   143,   144,
       0,     0,     0,     0,     0,     0,     0,   317,   318,     0,
       0,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,    72,    73,   156,   252,   157,     0,   320,     0,
       0,     0,     0,   253,   254,     0,   321,   322,     0,     0,
     256,     0,     0,   323,     0,   139,   257,   140,     0,   324,
     325,   258,   326,     0,   327,     0,     0,     0,     0,     0,
       0,   141,     0,     0,   330,   331,     0,     0,   211,     0,
       0,     0,     0,     0,     0,     0,   142,     0,     0,     0,
       0,     0,     0,   139,     0,   140,     0,   143,   144,     0,
       0,     0,     0,   332,     0,     0,     0,     0,     0,   141,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,    72,    73,   156,   142,   157,     0,     0,     0,     0,
       0,   139,     0,   140,     0,   143,   144,     0,     0,     0,
       0,     0,     0,     0,   281,     0,     0,   141,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,    72,
      73,   156,   142,   157,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   143,   144,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,    72,    73,   156,
       0,   157
};

static const yytype_int16 yycheck[] =
{
       0,     0,    73,     0,    18,   393,     7,   410,    17,    15,
       3,   213,    10,    14,    81,    82,    30,    17,    42,    33,
      29,    35,    12,    15,   133,     5,   228,   271,   272,    29,
      27,    32,    49,   134,   359,    80,    15,   362,    36,    42,
      26,    15,    14,    13,    15,    14,    49,    15,     4,     7,
      15,    51,    51,     9,    51,    11,   129,   130,    15,    42,
      55,    54,    15,    64,   109,    35,    67,    68,    69,    62,
      15,    15,    15,    63,    74,    74,     0,    74,    15,    15,
      15,   129,    66,    39,    66,   129,    44,    43,    14,    15,
     114,   134,    64,    44,    27,    64,   205,    73,    80,    55,
      56,    52,    53,    59,    60,    85,    86,    58,    59,   133,
      66,   114,    68,    64,    65,    48,   109,   134,    49,    70,
     364,   116,    96,   102,   110,    96,   132,    51,    96,    49,
     133,    96,    45,   109,    49,    25,     3,     4,   118,    96,
     132,     8,     9,    96,    11,    12,   471,    51,   132,   552,
      74,    96,    96,    96,   129,    70,   107,    23,    24,    96,
      96,    96,    52,    23,    24,    69,    64,    66,    64,   120,
     103,   122,    39,   124,   125,   126,    43,    73,    64,    83,
     131,   171,     0,   134,    88,     7,     8,    54,    55,    56,
      42,   579,    59,    60,   109,    62,    63,     3,     4,    66,
       9,    68,    68,   204,   213,    14,    66,   274,    68,    15,
     211,   133,   537,   213,   213,    81,   132,    23,    24,   228,
      80,    81,    44,   102,   225,   129,   130,   131,   228,   228,
     129,   130,   131,   132,    15,   134,    80,    43,    44,     7,
       8,     9,   109,   109,    64,    64,    52,    53,    64,   109,
      64,   185,    96,    59,    73,   129,   130,   131,    73,    65,
      66,    64,    68,   264,    70,   109,    64,    64,    66,    75,
      76,   272,   139,    64,    80,    81,    44,   233,   268,   235,
     270,   271,   272,   485,   218,   285,   285,   221,    64,   290,
      96,   284,   388,   389,    80,   129,   130,   131,    64,   255,
     167,    80,    64,   109,   171,   129,   130,   131,   264,   107,
      96,    64,    64,   303,   304,    64,    15,    96,   129,   130,
     131,   311,   120,   109,   122,   281,   124,   125,   126,    15,
     109,   132,    66,   131,   132,    15,   134,    64,   294,   108,
      64,   342,   132,    15,    44,   346,    14,   114,    15,   350,
     351,    15,    52,    53,   347,   353,    15,   358,    58,    59,
      15,   361,   361,    15,   361,    65,   233,    15,   235,    25,
      70,   132,   373,   132,    12,    15,   134,   375,   134,    15,
      80,   132,   383,    14,    96,    14,    81,   388,   255,   129,
      64,    64,    14,   393,   393,    48,   393,   264,   399,    48,
      14,   268,    15,   270,   271,   272,   104,   353,    87,   109,
     374,    74,   375,   525,   281,   408,   363,   284,   552,   284,
      62,   388,   285,   389,   228,   485,   340,   294,   492,   537,
      57,   227,   569,   389,   107,   207,   303,   304,   509,   379,
     307,    -1,    -1,   310,   311,   312,    -1,   120,    -1,   122,
      -1,   124,   125,   126,   468,   469,    -1,    -1,   131,    -1,
      -1,   134,    -1,    -1,   465,    -1,   333,   334,   335,   336,
     337,   338,   339,   139,   140,   141,   485,    -1,    -1,    -1,
     347,    -1,    14,   484,    -1,   485,   485,    -1,   489,    -1,
      -1,    -1,    44,    -1,    -1,   496,    -1,    -1,    -1,    -1,
      52,    53,    -1,    -1,    -1,   506,    58,    59,    -1,   510,
      -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    70,   512,
      -1,    -1,   389,    -1,   525,    -1,   527,   528,    80,    -1,
      -1,   532,    64,    -1,    66,   491,    -1,    -1,    -1,    -1,
      -1,   408,   498,    -1,    96,    -1,    -1,    -1,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   109,    -1,    -1,
      -1,    -1,    -1,    95,   565,    -1,    -1,   568,    -1,    -1,
      -1,    -1,   573,    -1,   106,   107,    -1,    -1,    -1,   579,
     579,    -1,   579,    -1,   540,    -1,    -1,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,    -1,   134,    -1,   560,    -1,   562,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   491,    -1,    -1,    -1,    -1,    -1,
      -1,   498,    -1,    -1,    -1,    -1,   302,    -1,    -1,   305,
     306,    -1,   308,    -1,    -1,   512,   312,    -1,    -1,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,    -1,    -1,     1,
      -1,    -1,    -1,   540,     6,   341,    -1,    -1,    10,    11,
      -1,    13,    -1,    -1,    16,    17,    18,    19,    20,    21,
      22,    -1,    -1,   560,    -1,   562,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    -1,    -1,    -1,    46,    47,    -1,    -1,    50,    51,
      -1,    -1,    54,    55,    56,    57,    -1,    -1,    60,    61,
      62,    63,    -1,    -1,    -1,    67,    -1,    -1,    -1,    71,
      72,    -1,    74,    -1,    -1,    77,    78,    79,    -1,    -1,
      82,    83,    84,    -1,    86,    -1,    -1,    89,    90,    91,
      92,    93,    94,    -1,    -1,    97,    98,    99,   100,   101,
     102,    -1,    -1,   105,   106,    -1,    -1,    -1,    -1,   111,
     112,   113,   114,    -1,   116,   117,   118,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,   130,   131,
     132,   133,    -1,    -1,    10,    11,    -1,    13,    -1,    -1,
      -1,    17,    18,    19,    20,    21,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      46,    47,    -1,    -1,    50,    51,    -1,   513,    54,    55,
      56,    57,    -1,    -1,    -1,    61,    -1,    63,    -1,    -1,
      -1,    67,    -1,    -1,    -1,    -1,    72,    -1,    74,    -1,
      -1,    77,    78,    79,    -1,    -1,    82,    83,    -1,    -1,
      86,    -1,    -1,    -1,    90,    91,    92,    93,    94,    -1,
      -1,    97,    -1,    -1,   100,   101,   102,    -1,    -1,   105,
     106,    -1,    -1,    -1,    -1,   111,   112,   113,   114,    -1,
     116,   117,   118,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      11,    -1,    13,   129,   130,   131,    17,    -1,    19,    20,
      21,    -1,    -1,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    53,    -1,    -1,    -1,    37,    58,    59,    -1,
      -1,    -1,    -1,    -1,    65,    46,    47,    -1,    -1,    70,
      -1,    -1,    -1,    -1,    -1,    56,    57,    -1,    -1,    80,
      61,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,
      -1,    72,    -1,    74,    -1,    96,    77,    -1,    79,    -1,
      -1,    82,     3,     4,    -1,    86,    -1,    -1,   109,    -1,
      91,    92,    93,    94,    -1,    -1,    97,    -1,    -1,   100,
     101,   102,    23,    24,   105,   106,    -1,    -1,    -1,    -1,
     111,   112,   113,    -1,    -1,    -1,    -1,   118,    -1,    -1,
      -1,    -1,    43,    44,    -1,    -1,    -1,    -1,   129,   130,
     131,    52,    53,    -1,    -1,    -1,     3,     4,    59,    -1,
      -1,    -1,    -1,    -1,    65,    66,    -1,    68,    -1,    70,
      -1,    -1,    -1,    -1,    75,    76,    23,    24,    -1,    80,
      81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    96,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    53,    -1,   109,    -1,
       3,     4,    59,    -1,    -1,    -1,    -1,    -1,    65,    66,
      -1,    68,    -1,    70,    -1,    -1,    -1,    -1,    75,    76,
      23,    24,    -1,    80,    81,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    96,
      43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,
      53,    -1,   109,    -1,     3,     4,    59,    -1,    -1,    -1,
      -1,    -1,    65,    66,    -1,    68,    -1,    70,    -1,    -1,
      -1,    -1,    75,    76,    23,    24,    -1,    80,    81,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    96,    43,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    53,    -1,   109,    -1,     3,     4,
      59,    -1,    -1,    -1,    -1,    -1,    65,    66,    -1,    68,
      -1,    70,    -1,    -1,    -1,    -1,    75,    76,    23,    24,
      -1,    80,    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    96,    43,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    53,    -1,
     109,    -1,     3,     4,    59,    -1,    -1,    -1,    -1,    -1,
      65,    66,    -1,    68,    -1,    70,    -1,    -1,    -1,    -1,
      75,    76,    23,    24,    -1,    80,    81,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    96,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    53,    -1,   109,    -1,     3,     4,    59,    -1,
      -1,    -1,    -1,    -1,    65,    66,    -1,    68,    -1,    70,
      -1,    -1,    -1,    -1,    75,    76,    23,    24,    -1,    80,
      81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    96,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    53,    -1,   109,    -1,
      -1,    -1,    59,    -1,    -1,    -1,    44,    -1,    65,    66,
      -1,    68,    -1,    70,    52,    53,    -1,    -1,    75,    76,
      58,    59,    -1,    80,    81,    -1,    64,    65,    66,    -1,
      -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   109,    -1,    -1,    -1,    -1,    95,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   106,   107,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,    24,    -1,
      -1,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,    44,   134,    -1,    44,    -1,
      -1,    -1,    -1,    52,    53,    -1,    52,    53,    -1,    -1,
      59,    -1,    -1,    59,    -1,    64,    65,    66,    -1,    65,
      66,    70,    68,    -1,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    80,    -1,    -1,    80,    81,    -1,    -1,    49,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    95,    -1,    -1,    -1,
      -1,    -1,    -1,    64,    -1,    66,    -1,   106,   107,    -1,
      -1,    -1,    -1,   109,    -1,    -1,    -1,    -1,    -1,    80,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,    95,   134,    -1,    -1,    -1,    -1,
      -1,    64,    -1,    66,    -1,   106,   107,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   115,    -1,    -1,    80,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,    95,   134,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   106,   107,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
      -1,   134
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,     1,     6,    10,    11,    13,    16,    17,    18,    19,
      20,    21,    22,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    46,    47,    50,
      51,    54,    55,    56,    57,    60,    61,    62,    63,    67,
      71,    72,    74,    77,    78,    79,    82,    83,    84,    86,
      89,    90,    91,    92,    93,    94,    97,    98,    99,   100,
     101,   102,   105,   106,   111,   112,   113,   114,   116,   117,
     118,   129,   130,   131,   132,   133,   137,   138,   139,   140,
     141,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   164,   172,   173,
     175,   176,   179,   180,   181,   183,   185,   187,   188,   189,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   207,   214,   215,   216,   217,   218,   219,   224,
     225,   244,   245,   246,   247,    42,    15,   132,   144,    64,
      66,    80,    95,   106,   107,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   132,   134,   225,   226,
     227,   228,   229,   230,   232,   245,   247,    64,   229,   230,
      49,   241,   227,   230,   226,   257,    66,   132,   142,   229,
     129,   130,   131,   165,   166,   255,   229,   231,   257,   142,
     227,   236,   244,   131,   238,   254,   255,   129,   239,   239,
     134,   225,    55,   116,   174,   244,   254,   227,   182,   253,
     254,    49,   134,   184,   248,   134,   142,   254,   131,   162,
     163,   255,   134,   259,   229,    49,   229,   129,   240,   248,
      15,   132,   143,    19,    47,    97,   112,   147,   239,   226,
     237,   229,   229,   259,   229,   229,   237,   257,   227,    45,
     229,   227,    44,    52,    53,    58,    59,    65,    70,   208,
     209,   210,   211,   212,   213,   227,   229,   227,   248,    14,
      64,    64,    64,   234,   145,   146,   147,     0,    42,   139,
     139,   115,   191,   226,   248,   102,     7,     8,     9,    44,
     220,   222,   223,     8,   221,   222,   132,    15,   228,   230,
     228,   228,    64,    64,    64,    64,    64,    64,    64,   233,
      64,    64,    64,    73,   260,     3,     4,    23,    24,    43,
      44,    52,    53,    59,    65,    66,    68,    70,    75,    76,
      80,    81,   109,    44,    52,    53,    58,    59,    65,    70,
      80,   109,    64,   234,   230,   257,    15,    15,   132,    66,
      64,    73,   169,    15,   169,   108,   262,   227,   222,    64,
     250,   262,    15,    14,    64,   227,    14,   242,   243,   244,
     246,    15,    15,    73,   169,    15,   168,   169,   227,   250,
     242,   132,    15,   114,    66,    80,   206,   229,    15,    15,
     227,   229,    25,   261,   257,   256,   257,   256,   257,    14,
     227,   235,   256,   257,   139,   229,    15,   102,   192,   193,
     191,   219,   227,   229,   132,    96,    96,   228,   257,   257,
     228,   228,   230,   228,   230,   257,   228,   230,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   230,   230,   230,   230,
     230,   230,   230,   232,   228,   227,   227,   226,   132,   170,
     171,   227,   227,    73,   109,   167,   166,   227,    51,    69,
      83,    88,   251,   252,   253,   254,    12,   264,   147,   258,
     253,   182,   256,    14,    15,    15,   134,   134,   227,   167,
     163,    15,   264,   132,   227,   210,   213,   212,   213,   258,
      15,    96,    96,    96,    96,   227,    14,    96,    96,    96,
      14,   226,   192,    15,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    15,    96,     9,    14,   227,
      26,   110,   177,   254,   254,   129,   253,    15,    96,    27,
      48,   103,   249,    96,   227,   243,   227,   229,   249,    14,
     227,   234,   190,   227,   228,   171,   227,   227,   227,   252,
      48,   229,    48,    14,    15,   192,   193,    96,   104,   178,
     229,   229,     5,    85,    86,   118,   186,   227,   227,   261,
     227,   258,    87,   263
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int16 yyr1[] =
{
       0,   136,   137,   137,   138,   138,   138,   138,   138,   139,
     139,   140,   140,   140,   140,   140,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   141,   141,   141,   141,   141,
     142,   142,   142,   142,   142,   143,   143,   143,   143,   144,
     144,   144,   144,   145,   145,   145,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   149,   149,   149,   149,   149,
     150,   151,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   162,   163,   163,   163,   163,   163,
     164,   165,   165,   166,   166,   166,   166,   167,   167,   168,
     168,   169,   170,   170,   171,   171,   171,   172,   173,   174,
     174,   175,   176,   177,   177,   178,   178,   179,   180,   181,
     181,   182,   182,   183,   184,   184,   184,   185,   186,   186,
     186,   186,   187,   188,   188,   188,   188,   189,   189,   190,
     190,   191,   191,   192,   192,   193,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     206,   207,   208,   208,   209,   209,   210,   210,   211,   211,
     212,   212,   212,   213,   213,   213,   213,   213,   213,   214,
     215,   216,   217,   218,   218,   219,   219,   220,   220,   221,
     221,   222,   222,   223,   223,   224,   225,   225,   225,   226,
     226,   227,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   229,   230,   230,   230,   231,   231,   232,   232,
     232,   232,   232,   232,   232,   232,   232,   232,   233,   233,
     234,   235,   235,   235,   235,   236,   236,   237,   237,   238,
     238,   239,   239,   240,   240,   241,   241,   242,   242,   243,
     243,   244,   245,   245,   245,   245,   246,   247,   247,   247,
     247,   247,   248,   248,   249,   249,   249,   249,   250,   250,
     251,   251,   252,   252,   252,   252,   252,   253,   253,   254,
     254,   255,   255,   256,   256,   257,   257,   258,   258,   259,
     259,   260,   260,   261,   261,   262,   262,   263,   263,   264,
     264
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     1,     3,     2,     2,     1,     1,
       0,     1,     1,     2,     2,     2,     2,     1,     1,     1,
       2,     1,     2,     2,     2,     2,     2,     4,     2,     4,
       0,     1,     2,     2,     3,     1,     3,     2,     0,     1,
       3,     2,     0,     1,     1,     0,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     3,     4,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     3,     1,     2,     1,     3,     4,     2,
       2,     3,     1,     2,     3,     4,     2,     1,     1,     1,
       0,     3,     3,     1,     1,     3,     3,     3,     3,     1,
       1,     2,     9,     1,     1,     2,     0,     5,     4,     4,
       2,     3,     1,     3,     1,     2,     0,     7,     1,     1,
       1,     3,     2,     1,     3,     6,     3,     1,     1,     3,
       1,     3,     1,     1,     1,     1,     0,     5,     3,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     3,     1,
       1,     2,     1,     1,     3,     1,     2,     1,     3,     1,
       2,     1,     2,     1,     1,     1,     1,     1,     1,     4,
       4,     3,     1,     3,     1,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     4,     4,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     1,
       1,     1,     4,     4,     4,     4,     1,     4,     6,     1,
       4,     3,     1,     3,     1,     3,     1,     0,     1,     2,
       4,     4,     1,     2,     1,     4,     4,     3,     3,     0,
       3,     3,     2,     2,     3,     1,     0,     1,     0,     1,
       0,     1,     0,     1,     0,     1,     0,     3,     1,     1,
       1,     1,     1,     1,     4,     4,     1,     1,     4,     2,
       5,     4,     3,     5,     2,     3,     3,     0,     3,     0,
       3,     1,     1,     2,     2,     2,     2,     1,     4,     1,
       1,     1,     1,     2,     0,     3,     1,     1,     0,     1,
       0,     1,     0,     1,     0,     1,     0,     1,     0,     1,
       0
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* a_comal_line: comal_line eolnSYM  */
#line 243 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				c_line=(yyvsp[-1].cl);
				YYACCEPT;
			}
#line 2049 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 3: /* a_comal_line: error eolnSYM  */
#line 248 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				p_error("Syntax error");
				yyerrok;
				c_line.cmd=0;
				YYACCEPT;
			}
#line 2060 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 4: /* comal_line: command  */
#line 257 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl)=(yyvsp[0].cl);
				(yyval.cl).ld=NULL;
			}
#line 2069 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 5: /* comal_line: intnumSYM program_line optrem  */
#line 262 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl)=(yyvsp[-1].cl);
				(yyval.cl).ld=PARS_ALLOC(struct comal_line_data);
				(yyval.cl).ld->lineno=(yyvsp[-2].num);
				(yyval.cl).ld->rem=(yyvsp[0].str);
				(yyval.cl).lineptr=NULL;
			}
#line 2081 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 6: /* comal_line: complex_stat optrem  */
#line 270 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl)=(yyvsp[-1].cl);
				(yyval.cl).ld=NULL;
				if ((yyvsp[0].str)) {
					(yyval.cl).ld=PARS_ALLOC(struct comal_line_data);
					(yyval.cl).ld->lineno=0;
					(yyval.cl).ld->rem=(yyvsp[0].str);
				}
			}
#line 2095 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 7: /* comal_line: simple_stat optrem  */
#line 280 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl)=(yyvsp[-1].cl);
				(yyval.cl).ld=NULL;
				if ((yyvsp[0].str)) {
					(yyval.cl).ld=PARS_ALLOC(struct comal_line_data);
					(yyval.cl).ld->lineno=0;
					(yyval.cl).ld->rem=(yyvsp[0].str);
				}
			}
#line 2109 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 8: /* comal_line: optrem  */
#line 290 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=0;
			}
#line 2117 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 10: /* optrem: %empty  */
#line 297 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.str)=NULL;
			}
#line 2125 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 11: /* command: quitSYM  */
#line 304 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=quitSYM;
			}
#line 2133 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 13: /* command: saveSYM optfilename  */
#line 309 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=saveSYM;
				(yyval.cl).lc.str=(yyvsp[0].str);
			}
#line 2142 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 14: /* command: loadSYM optfilename  */
#line 314 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=loadSYM;
				(yyval.cl).lc.str=(yyvsp[0].str);
			}
#line 2151 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 15: /* command: enterSYM stringSYM  */
#line 319 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=enterSYM;
				(yyval.cl).lc.str=(yyvsp[0].str);
			}
#line 2160 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 16: /* command: envSYM optid2  */
#line 324 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=envSYM;
				(yyval.cl).lc.id=(yyvsp[0].id);
			}
#line 2169 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 17: /* command: runSYM  */
#line 329 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=COMMAND(runSYM);
				(yyval.cl).lc.str=NULL;
			}
#line 2178 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 18: /* command: newSYM  */
#line 334 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=newSYM;
			}
#line 2186 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 19: /* command: scanSYM  */
#line 338 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=scanSYM;
			}
#line 2194 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 20: /* command: autoSYM autolines  */
#line 342 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=autoSYM;
				(yyval.cl).lc.twonum=(yyvsp[0].twonum);
			}
#line 2203 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 21: /* command: contSYM  */
#line 347 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=contSYM;
			}
#line 2211 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 22: /* command: delSYM line_range  */
#line 351 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=COMMAND(delSYM);
				(yyval.cl).lc.twonum=(yyvsp[0].twonum);
			}
#line 2220 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 23: /* command: editSYM line_range  */
#line 356 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=editSYM;
				(yyval.cl).lc.twonum=(yyvsp[0].twonum);
			}
#line 2229 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 24: /* command: renumberSYM renumlines  */
#line 361 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=renumberSYM;
				(yyval.cl).lc.twonum=(yyvsp[0].twonum);
			}
#line 2238 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 25: /* list_cmd: listSYM line_range  */
#line 368 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=listSYM;
				(yyval.cl).lc.listrec.str=NULL;
				(yyval.cl).lc.listrec.twonum=(yyvsp[0].twonum);
				(yyval.cl).lc.listrec.id=NULL;
			}
#line 2249 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 26: /* list_cmd: listSYM stringSYM  */
#line 375 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=listSYM;
				(yyval.cl).lc.listrec.str=(yyvsp[0].str);
				(yyval.cl).lc.listrec.twonum.num1=0;
				(yyval.cl).lc.listrec.twonum.num2=INT_MAX;
				(yyval.cl).lc.listrec.id=NULL;
			}
#line 2261 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 27: /* list_cmd: listSYM line_range commaSYM stringSYM  */
#line 383 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=listSYM;
				(yyval.cl).lc.listrec.str=(yyvsp[0].str);
				(yyval.cl).lc.listrec.twonum=(yyvsp[-2].twonum);
				(yyval.cl).lc.listrec.id=NULL;
			}
#line 2272 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 28: /* list_cmd: listSYM id  */
#line 390 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=listSYM;
				(yyval.cl).lc.listrec.str=NULL;
				(yyval.cl).lc.listrec.id=(yyvsp[0].id);
			}
#line 2282 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 29: /* list_cmd: listSYM id commaSYM stringSYM  */
#line 396 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=listSYM;
				(yyval.cl).lc.listrec.str=(yyvsp[0].str);
				(yyval.cl).lc.listrec.id=(yyvsp[-2].id);
			}
#line 2292 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 30: /* line_range: %empty  */
#line 404 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twonum).num1=0;	(yyval.twonum).num2=INT_MAX;
			}
#line 2300 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 31: /* line_range: intnumSYM  */
#line 408 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twonum).num1=(yyvsp[0].num);	(yyval.twonum).num2=(yyvsp[0].num);
			}
#line 2308 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 32: /* line_range: minusSYM intnumSYM  */
#line 412 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twonum).num1=0;	(yyval.twonum).num2=(yyvsp[0].num);
			}
#line 2316 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 33: /* line_range: intnumSYM minusSYM  */
#line 416 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twonum).num1=(yyvsp[-1].num);	(yyval.twonum).num2=INT_MAX;
			}
#line 2324 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 34: /* line_range: intnumSYM minusSYM intnumSYM  */
#line 420 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twonum).num1=(yyvsp[-2].num);	(yyval.twonum).num2=(yyvsp[0].num);
			}
#line 2332 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 35: /* renumlines: intnumSYM  */
#line 426 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twonum).num1=(yyvsp[0].num);	(yyval.twonum).num2=10;
			}
#line 2340 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 36: /* renumlines: intnumSYM commaSYM intnumSYM  */
#line 430 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twonum).num1=(yyvsp[-2].num);	(yyval.twonum).num2=(yyvsp[0].num);
			}
#line 2348 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 37: /* renumlines: commaSYM intnumSYM  */
#line 434 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twonum).num1=10;	(yyval.twonum).num2=(yyvsp[0].num);
			}
#line 2356 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 38: /* renumlines: %empty  */
#line 438 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twonum).num1=10;	(yyval.twonum).num2=10;
			}
#line 2364 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 39: /* autolines: intnumSYM  */
#line 444 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twonum).num1=(yyvsp[0].num);	(yyval.twonum).num2=10;
			}
#line 2372 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 40: /* autolines: intnumSYM commaSYM intnumSYM  */
#line 448 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twonum).num1=(yyvsp[-2].num);	(yyval.twonum).num2=(yyvsp[0].num);
			}
#line 2380 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 41: /* autolines: commaSYM intnumSYM  */
#line 452 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twonum).num1=prog_highest_line()+(yyvsp[0].num);	
				(yyval.twonum).num2=(yyvsp[0].num);
			}
#line 2389 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 42: /* autolines: %empty  */
#line 457 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twonum).num1=prog_highest_line()+10;	
				(yyval.twonum).num2=10;
			}
#line 2398 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 45: /* program_line: %empty  */
#line 466 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=0;
			}
#line 2406 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 88: /* simple_stat: xid  */
#line 516 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=execSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 2415 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 91: /* complex_1word: elseSYM  */
#line 525 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=elseSYM;
			}
#line 2423 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 92: /* complex_1word: endcaseSYM  */
#line 529 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=endcaseSYM;
			}
#line 2431 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 93: /* complex_1word: endfuncSYM optid  */
#line 533 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=endfuncSYM;
			}
#line 2439 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 94: /* complex_1word: endifSYM  */
#line 537 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=endifSYM;
			}
#line 2447 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 95: /* complex_1word: loopSYM  */
#line 541 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=loopSYM;
			}
#line 2455 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 96: /* complex_1word: endloopSYM  */
#line 545 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=endloopSYM;
			}
#line 2463 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 97: /* complex_1word: endprocSYM optid2  */
#line 549 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=endprocSYM;
			}
#line 2471 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 98: /* complex_1word: endwhileSYM  */
#line 553 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=endwhileSYM;
			}
#line 2479 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 99: /* complex_1word: endforSYM optnumlvalue  */
#line 557 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=endforSYM;
			}
#line 2487 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 100: /* complex_1word: otherwiseSYM  */
#line 561 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=otherwiseSYM;
			}
#line 2495 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 101: /* complex_1word: repeatSYM  */
#line 565 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=repeatSYM;
				(yyval.cl).lc.ifwhilerec.exp=NULL;
				(yyval.cl).lc.ifwhilerec.stat=NULL;
			}
#line 2505 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 102: /* complex_1word: trapSYM  */
#line 571 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=trapSYM;
				(yyval.cl).lc.traprec.esc=0;
			}
#line 2514 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 103: /* complex_1word: handlerSYM  */
#line 576 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=handlerSYM;
			}
#line 2522 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 104: /* complex_1word: endtrapSYM  */
#line 580 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=endtrapSYM;
			}
#line 2530 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 105: /* simple_1word: nullSYM  */
#line 586 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=nullSYM;
			}
#line 2538 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 106: /* simple_1word: endSYM  */
#line 590 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=endSYM;
			}
#line 2546 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 107: /* simple_1word: exitSYM  */
#line 594 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=exitSYM;
				(yyval.cl).lc.exp=NULL;
			}
#line 2555 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 108: /* simple_1word: pageSYM  */
#line 599 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=pageSYM;
			}
#line 2563 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 109: /* simple_1word: retrySYM  */
#line 603 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=retrySYM;
			}
#line 2571 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 110: /* case_stat: caseSYM exp optof  */
#line 609 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=caseSYM;
				(yyval.cl).lc.exp=(yyvsp[-1].exp);
			}
#line 2580 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 111: /* close_stat: closeSYM  */
#line 616 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=closeSYM;
				(yyval.cl).lc.exproot=NULL;
			}
#line 2589 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 112: /* close_stat: closeSYM optfileS exp_list  */
#line 621 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=closeSYM;
				(yyval.cl).lc.exproot=PARS_REVERSE(struct exp_list, (yyvsp[0].expptr));
			}
#line 2598 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 113: /* cursor_stat: cursorSYM numexp commaSYM numexp  */
#line 628 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=cursorSYM;
				(yyval.cl).lc.twoexp.exp1=(yyvsp[-2].exp);
				(yyval.cl).lc.twoexp.exp2=(yyvsp[0].exp);
			}
#line 2608 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 114: /* chdir_stat: chdirSYM stringexp  */
#line 636 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=chdirSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 2617 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 115: /* rmdir_stat: rmdirSYM stringexp  */
#line 643 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=rmdirSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 2626 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 116: /* mkdir_stat: mkdirSYM stringexp  */
#line 650 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=mkdirSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 2635 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 117: /* data_stat: dataSYM exp_list  */
#line 657 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=dataSYM;
				(yyval.cl).lc.exproot=PARS_REVERSE(struct exp_list, (yyvsp[0].expptr));
			}
#line 2644 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 118: /* draw_stat: drawSYM exp_list  */
#line 664 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=drawSYM;
				(yyval.cl).lc.exproot=PARS_REVERSE(struct exp_list, (yyvsp[0].expptr));
				/* Auto-quote: if the first expression is a bare
				   identifier (no subscripts), treat it as a
				   string constant — e.g. DRAW circle, 100, 200, 50
				   becomes DRAW "circle", 100, 200, 50 */
				struct exp_list *first = (yyval.cl).lc.exproot;
				if (first && first->exp) {
					struct expression *inner = first->exp;
					if (inner->optype == T_EXP_IS_NUM)
						inner = inner->e.exp;
					if (inner->optype == T_ID &&
					    inner->e.expid.exproot == NULL) {
						first->exp = pars_exp_string_from_name(
							inner->e.expid.id->name);
					}
				}
			}
#line 2668 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 119: /* del_stat: delSYM stringexp  */
#line 686 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=delSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 2677 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 120: /* dir_stat: dirSYM opt_stringexp  */
#line 693 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=dirSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 2686 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 121: /* unit_stat: unitSYM stringexp  */
#line 700 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=unitSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 2695 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 122: /* local_stat: localSYM local_list  */
#line 708 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=localSYM;
				(yyval.cl).lc.dimroot=PARS_REVERSE(struct dim_list, (yyvsp[0].dimptr));
			}
#line 2704 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 123: /* local_list: local_list commaSYM local_item  */
#line 714 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=(yyvsp[0].dimptr);
				(yyval.dimptr)->next=(yyvsp[-2].dimptr);
			}
#line 2713 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 124: /* local_list: local_item  */
#line 719 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=(yyvsp[0].dimptr);
				(yyval.dimptr)->next=NULL;
			}
#line 2722 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 125: /* local_item: numid opt_dim_ensions  */
#line 726 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[-1].id),NULL,(yyvsp[0].dimensionptr));
			}
#line 2730 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 126: /* local_item: stringidSYM  */
#line 730 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[0].id),NULL,NULL);
			}
#line 2738 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 127: /* local_item: stringidSYM ofSYM numexp  */
#line 734 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[-2].id),(yyvsp[0].exp),NULL);
			}
#line 2746 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 128: /* local_item: stringidSYM dim_ensions of numexp  */
#line 738 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[-3].id),(yyvsp[0].exp),(yyvsp[-2].dimensionptr));
			}
#line 2754 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 129: /* local_item: stringidSYM dim_ensions  */
#line 742 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[-1].id),NULL,(yyvsp[0].dimensionptr));
			}
#line 2762 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 130: /* dim_stat: dimSYM dim_list  */
#line 749 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=dimSYM;
				(yyval.cl).lc.dimroot=PARS_REVERSE(struct dim_list, (yyvsp[0].dimptr));
			}
#line 2771 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 131: /* dim_list: dim_list commaSYM dim_item  */
#line 756 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=(yyvsp[0].dimptr);
				(yyval.dimptr)->next=(yyvsp[-2].dimptr);
			}
#line 2780 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 132: /* dim_list: dim_item  */
#line 761 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=(yyvsp[0].dimptr);
				(yyval.dimptr)->next=NULL;
			}
#line 2789 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 133: /* dim_item: numid dim_ensions  */
#line 768 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[-1].id),NULL,(yyvsp[0].dimensionptr));
			}
#line 2797 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 134: /* dim_item: stringidSYM ofSYM numexp  */
#line 772 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[-2].id),(yyvsp[0].exp),NULL);
			}
#line 2805 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 135: /* dim_item: stringidSYM dim_ensions of numexp  */
#line 776 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[-3].id),(yyvsp[0].exp),(yyvsp[-2].dimensionptr));
			}
#line 2813 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 136: /* dim_item: stringidSYM dim_ensions  */
#line 780 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[-1].id),NULL,(yyvsp[0].dimensionptr));
			}
#line 2821 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 140: /* opt_dim_ensions: %empty  */
#line 791 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimensionptr)=NULL;
			}
#line 2829 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 141: /* dim_ensions: lparenSYM dim_ension_list rparenSYM  */
#line 797 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimensionptr)=(yyvsp[-1].dimensionptr);
			}
#line 2837 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 142: /* dim_ension_list: dim_ension_list commaSYM dim_ension  */
#line 803 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimensionptr)=(yyvsp[0].dimensionptr);
				(yyval.dimensionptr)->next=(yyvsp[-2].dimensionptr);
			}
#line 2846 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 143: /* dim_ension_list: dim_ension  */
#line 808 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimensionptr)=(yyvsp[0].dimensionptr);
				(yyval.dimensionptr)->next=NULL;
			}
#line 2855 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 144: /* dim_ension: numexp  */
#line 815 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimensionptr)=PARS_ALLOC(struct dim_ension);
				(yyval.dimensionptr)->bottom=NULL;
				(yyval.dimensionptr)->top=(yyvsp[0].exp);
			}
#line 2865 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 145: /* dim_ension: numexp colonSYM numexp  */
#line 821 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimensionptr)=PARS_ALLOC(struct dim_ension);
				(yyval.dimensionptr)->bottom=(yyvsp[-2].exp);
				(yyval.dimensionptr)->top=(yyvsp[0].exp);
			}
#line 2875 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 146: /* dim_ension: numexp becminusSYM numexp  */
#line 827 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimensionptr)=PARS_ALLOC(struct dim_ension);
				(yyval.dimensionptr)->bottom=(yyvsp[-2].exp);
				(yyval.dimensionptr)->top=pars_exp_unary(minusSYM,(yyvsp[0].exp));
			}
#line 2885 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 147: /* elif_stat: elifSYM numexp optthen  */
#line 835 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=elifSYM;
				(yyval.cl).lc.exp=(yyvsp[-1].exp);
			}
#line 2894 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 148: /* exit_stat: exitSYM ifwhen numexp  */
#line 842 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=exitSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 2903 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 151: /* exec_stat: execSYM xid  */
#line 853 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=execSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 2912 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 152: /* for_stat: forSYM numlvalue assign1 numexp todownto numexp optstep optdo optsimple_stat  */
#line 860 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=forSYM;
				(yyval.cl).lc.forrec.lval=(yyvsp[-7].exp);
				(yyval.cl).lc.forrec.from=(yyvsp[-5].exp);
				(yyval.cl).lc.forrec.mode=(yyvsp[-4].inum);
				(yyval.cl).lc.forrec.to=(yyvsp[-3].exp);
				(yyval.cl).lc.forrec.step=(yyvsp[-2].exp);
				(yyval.cl).lc.forrec.stat=(yyvsp[0].pcl);
			}
#line 2926 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 153: /* todownto: toSYM  */
#line 872 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=toSYM;
			}
#line 2934 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 154: /* todownto: downtoSYM  */
#line 876 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=downtoSYM;
			}
#line 2942 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 155: /* optstep: stepSYM numexp  */
#line 882 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=(yyvsp[0].exp);
			}
#line 2950 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 156: /* optstep: %empty  */
#line 886 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=NULL;
			}
#line 2958 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 157: /* func_stat: funcSYM id procfunc_head optclosed opt_external  */
#line 892 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=funcSYM;
				(yyval.cl).lc.pfrec.id=(yyvsp[-3].id);
				(yyval.cl).lc.pfrec.parmroot=PARS_REVERSE(struct parm_list, (yyvsp[-2].parmptr));
				(yyval.cl).lc.pfrec.closed=(yyvsp[-1].inum);
				(yyval.cl).lc.pfrec.external=(yyvsp[0].extptr);
			}
#line 2970 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 158: /* if_stat: ifSYM numexp optthen optsimple_stat  */
#line 902 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=ifSYM;
				(yyval.cl).lc.ifwhilerec.exp=(yyvsp[-2].exp);
				(yyval.cl).lc.ifwhilerec.stat=(yyvsp[0].pcl);
			}
#line 2980 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 159: /* import_stat: importSYM id colonSYM import_list  */
#line 910 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=importSYM;
				(yyval.cl).lc.importrec.id=(yyvsp[-2].id);
				(yyval.cl).lc.importrec.importroot=PARS_REVERSE(struct import_list, (yyvsp[0].importptr));
			}
#line 2990 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 160: /* import_stat: importSYM import_list  */
#line 916 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=importSYM;
				(yyval.cl).lc.importrec.id=NULL;
				(yyval.cl).lc.importrec.importroot=PARS_REVERSE(struct import_list, (yyvsp[0].importptr));
			}
#line 3000 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 161: /* import_list: import_list commaSYM oneparm  */
#line 924 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.importptr)=PARS_ALLOC(struct import_list);
				(yyval.importptr)->id=(yyvsp[0].oneparm).id;
				(yyval.importptr)->array=(yyvsp[0].oneparm).array;
				(yyval.importptr)->next=(yyvsp[-2].importptr);				
			}
#line 3011 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 162: /* import_list: oneparm  */
#line 931 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.importptr)=PARS_ALLOC(struct import_list);
				(yyval.importptr)->id=(yyvsp[0].oneparm).id;
				(yyval.importptr)->array=(yyvsp[0].oneparm).array;
				(yyval.importptr)->next=NULL;
			}
#line 3022 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 163: /* input_stat: inputSYM input_modifier lval_list  */
#line 940 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=inputSYM;
				(yyval.cl).lc.inputrec.modifier=(yyvsp[-1].imod);
				(yyval.cl).lc.inputrec.lvalroot=PARS_REVERSE(struct exp_list, (yyvsp[0].expptr));
			}
#line 3032 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 164: /* input_modifier: file_designator  */
#line 948 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.imod)=PARS_ALLOC(struct input_modifier);
				(yyval.imod)->type=fileSYM;
				(yyval.imod)->data.twoexp=(yyvsp[0].twoexp);
			}
#line 3042 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 165: /* input_modifier: stringSYM colonSYM  */
#line 954 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.imod)=PARS_ALLOC(struct input_modifier);
				(yyval.imod)->type=stringSYM;
				(yyval.imod)->data.str=(yyvsp[-1].str);
			}
#line 3052 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 166: /* input_modifier: %empty  */
#line 960 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.imod)=NULL;
			}
#line 3060 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 167: /* open_stat: openSYM fileSYM numexp commaSYM stringexp commaSYM open_type  */
#line 966 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=openSYM;
				(yyval.cl).lc.openrec=(yyvsp[0].openrec);
				(yyval.cl).lc.openrec.filenum=(yyvsp[-4].exp);
				(yyval.cl).lc.openrec.filename=(yyvsp[-2].exp);
			}
#line 3071 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 168: /* open_type: readSYM  */
#line 975 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.openrec).type=readSYM;
			}
#line 3079 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 169: /* open_type: writeSYM  */
#line 979 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.openrec).type=writeSYM;
			}
#line 3087 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 170: /* open_type: appendSYM  */
#line 983 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.openrec).type=appendSYM;
			}
#line 3095 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 171: /* open_type: randomSYM numexp optread_only  */
#line 987 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.openrec).type=randomSYM;
				(yyval.openrec).reclen=(yyvsp[-1].exp);
				(yyval.openrec).read_only=(yyvsp[0].inum);
			}
#line 3105 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 172: /* os_stat: osSYM stringexp  */
#line 995 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=osSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 3114 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 173: /* print_stat: printi  */
#line 1002 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=printSYM;
				(yyval.cl).lc.printrec.modifier=NULL;
				(yyval.cl).lc.printrec.printroot=NULL;
				(yyval.cl).lc.printrec.pr_sep=0;
			}
#line 3125 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 174: /* print_stat: printi print_list optpr_sep  */
#line 1009 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=printSYM;
				(yyval.cl).lc.printrec.modifier=NULL;
				(yyval.cl).lc.printrec.printroot=PARS_REVERSE(struct print_list, (yyvsp[-1].printptr));
				(yyval.cl).lc.printrec.pr_sep=(yyvsp[0].inum);
			}
#line 3136 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 175: /* print_stat: printi usingSYM stringexp colonSYM prnum_list optpr_sep  */
#line 1016 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=printSYM;
				(yyval.cl).lc.printrec.modifier=PARS_ALLOC(struct print_modifier);
				(yyval.cl).lc.printrec.modifier->type=usingSYM;
				(yyval.cl).lc.printrec.modifier->data.str=(yyvsp[-3].exp);
				(yyval.cl).lc.printrec.printroot=PARS_REVERSE(struct print_list, (yyvsp[-1].printptr));
				(yyval.cl).lc.printrec.pr_sep=(yyvsp[0].inum);
			}
#line 3149 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 176: /* print_stat: printi file_designator print_list  */
#line 1025 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=printSYM;
				(yyval.cl).lc.printrec.modifier=PARS_ALLOC(struct print_modifier);
				(yyval.cl).lc.printrec.modifier->type=fileSYM;
				(yyval.cl).lc.printrec.modifier->data.twoexp=(yyvsp[-1].twoexp);
				(yyval.cl).lc.printrec.printroot=PARS_REVERSE(struct print_list, (yyvsp[0].printptr));
				(yyval.cl).lc.printrec.pr_sep=0;
			}
#line 3162 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 179: /* prnum_list: prnum_list pr_sep numexp  */
#line 1040 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.printptr)=pars_printlist_item((yyvsp[-1].inum),(yyvsp[0].exp),(yyvsp[-2].printptr));
			}
#line 3170 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 180: /* prnum_list: numexp  */
#line 1044 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.printptr)=pars_printlist_item(0,(yyvsp[0].exp),NULL);
			}
#line 3178 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 181: /* print_list: print_list pr_sep exp  */
#line 1050 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.printptr)=pars_printlist_item((yyvsp[-1].inum),(yyvsp[0].exp),(yyvsp[-2].printptr));
			}
#line 3186 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 182: /* print_list: exp  */
#line 1054 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.printptr)=pars_printlist_item(0,(yyvsp[0].exp),NULL);
			}
#line 3194 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 183: /* pr_sep: commaSYM  */
#line 1060 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=commaSYM;
			}
#line 3202 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 184: /* pr_sep: semicolonSYM  */
#line 1064 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=semicolonSYM;
			}
#line 3210 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 186: /* optpr_sep: %empty  */
#line 1071 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=0;
			}
#line 3218 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 187: /* proc_stat: procSYM idSYM procfunc_head optclosed opt_external  */
#line 1077 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=procSYM;
				(yyval.cl).lc.pfrec.id=(yyvsp[-3].id);
				(yyval.cl).lc.pfrec.parmroot=PARS_REVERSE(struct parm_list, (yyvsp[-2].parmptr));
				(yyval.cl).lc.pfrec.closed=(yyvsp[-1].inum);
				(yyval.cl).lc.pfrec.external=(yyvsp[0].extptr);
			}
#line 3230 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 188: /* read_stat: readSYM optfile lval_list  */
#line 1087 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=readSYM;
				(yyval.cl).lc.readrec.modifier=(yyvsp[-1].twoexpp);
				(yyval.cl).lc.readrec.lvalroot=PARS_REVERSE(struct exp_list, (yyvsp[0].expptr));
			}
#line 3240 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 189: /* restore_stat: restoreSYM optid2  */
#line 1095 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=restoreSYM;
				(yyval.cl).lc.id=(yyvsp[0].id);
			}
#line 3249 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 190: /* return_stat: returnSYM optexp  */
#line 1102 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=returnSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 3258 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 191: /* run_stat: runSYM stringexp  */
#line 1109 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=runSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 3267 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 192: /* select_out_stat: select_outputSYM stringexp  */
#line 1116 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=select_outputSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 3276 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 193: /* select_in_stat: select_inputSYM stringexp  */
#line 1124 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=select_inputSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 3285 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 194: /* stop_stat: stopSYM optexp  */
#line 1131 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=stopSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 3294 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 195: /* sys_stat: sysSYM exp_list  */
#line 1138 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=sysSYM;
				(yyval.cl).lc.exproot=PARS_REVERSE(struct exp_list, (yyvsp[0].expptr));
			}
#line 3303 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 196: /* until_stat: untilSYM numexp  */
#line 1145 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=untilSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 3312 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 197: /* trace_stat: traceSYM numexp  */
#line 1152 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				char *cmd=exp_cmd((yyvsp[0].exp));
				
				if (strcasecmp(cmd,"on")!=0 && strcasecmp(cmd,"off")!=0)
					pars_error("TRACE \"on\" or \"off\"");
				
				(yyval.cl).cmd=traceSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 3326 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 198: /* trap_stat: trapSYM escSYM plusorminus  */
#line 1164 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=trapSYM;
				(yyval.cl).lc.traprec.esc=(yyvsp[0].inum);
			}
#line 3335 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 199: /* plusorminus: plusSYM  */
#line 1171 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=plusSYM;
			}
#line 3343 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 200: /* plusorminus: minusSYM  */
#line 1175 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=minusSYM;
			}
#line 3351 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 201: /* when_stat: whenSYM when_list  */
#line 1181 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=whenSYM;
				(yyval.cl).lc.whenroot=PARS_REVERSE(struct when_list, (yyvsp[0].whenptr));
			}
#line 3360 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 204: /* when_numlist: when_numlist commaSYM when_numitem  */
#line 1192 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.whenptr)=(yyvsp[0].whenptr);
				(yyval.whenptr)->next=(yyvsp[-2].whenptr);
			}
#line 3369 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 206: /* when_numitem: relop numexp  */
#line 1200 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.whenptr)=pars_whenlist_item((yyvsp[-1].inum),(yyvsp[0].exp),NULL);
			}
#line 3377 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 207: /* when_numitem: numexp  */
#line 1204 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.whenptr)=pars_whenlist_item(eqlSYM,(yyvsp[0].exp),NULL);
			}
#line 3385 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 208: /* when_strlist: when_strlist commaSYM when_stritem  */
#line 1210 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.whenptr)=(yyvsp[0].whenptr);
				(yyval.whenptr)->next=(yyvsp[-2].whenptr);
			}
#line 3394 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 210: /* when_stritem: relop stringexp  */
#line 1218 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.whenptr)=pars_whenlist_item((yyvsp[-1].inum),(yyvsp[0].exp),NULL);
			}
#line 3402 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 211: /* when_stritem: stringexp  */
#line 1222 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.whenptr)=pars_whenlist_item(eqlSYM,(yyvsp[0].exp),NULL);
			}
#line 3410 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 212: /* when_stritem: inSYM stringexp  */
#line 1226 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.whenptr)=pars_whenlist_item(inSYM,(yyvsp[0].exp),NULL);
			}
#line 3418 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 213: /* relop: gtrSYM  */
#line 1232 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=gtrSYM;
			}
#line 3426 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 214: /* relop: lssSYM  */
#line 1236 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=lssSYM;
			}
#line 3434 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 215: /* relop: eqlSYM  */
#line 1240 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=eqlSYM;
			}
#line 3442 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 216: /* relop: neqSYM  */
#line 1244 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=neqSYM;
			}
#line 3450 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 217: /* relop: geqSYM  */
#line 1248 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=geqSYM;
			}
#line 3458 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 218: /* relop: leqSYM  */
#line 1252 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=leqSYM;
			}
#line 3466 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 219: /* while_stat: whileSYM numexp optdo optsimple_stat  */
#line 1258 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=whileSYM;
				(yyval.cl).lc.ifwhilerec.exp=(yyvsp[-2].exp);
				(yyval.cl).lc.ifwhilerec.stat=(yyvsp[0].pcl);
			}
#line 3476 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 220: /* repeat_stat: repeatSYM simple_stat untilSYM numexp  */
#line 1266 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=repeatSYM;
				(yyval.cl).lc.ifwhilerec.exp=(yyvsp[0].exp);
				(yyval.cl).lc.ifwhilerec.stat=stat_dup(&(yyvsp[-2].cl));
			}
#line 3486 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 221: /* write_stat: writeSYM file_designator exp_list  */
#line 1274 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=writeSYM;
				(yyval.cl).lc.writerec.twoexp=(yyvsp[-1].twoexp);
				(yyval.cl).lc.writerec.exproot=PARS_REVERSE(struct exp_list, (yyvsp[0].expptr));
			}
#line 3496 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 222: /* assign_stat: assign_list  */
#line 1282 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=becomesSYM;
				(yyval.cl).lc.assignroot=PARS_REVERSE(struct assign_list, (yyvsp[0].assignptr));
			}
#line 3505 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 223: /* assign_list: assign_list semicolonSYM assign_item  */
#line 1289 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.assignptr)=(yyvsp[0].assignptr);
				(yyval.assignptr)->next=(yyvsp[-2].assignptr);
			}
#line 3514 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 224: /* assign_list: assign_item  */
#line 1294 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.assignptr)->next=NULL;
			}
#line 3522 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 225: /* assign_item: numlvalue nassign numexp  */
#line 1300 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.assignptr)=pars_assign_item((yyvsp[-1].inum),(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3530 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 226: /* assign_item: strlvalue sassign stringexp  */
#line 1304 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.assignptr)=pars_assign_item((yyvsp[-1].inum),(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3538 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 230: /* sassign: becplusSYM  */
#line 1315 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=becplusSYM;
			}
#line 3546 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 231: /* assign1: eqlSYM  */
#line 1321 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=becomesSYM;
			}
#line 3554 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 232: /* assign1: becomesSYM  */
#line 1325 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=becomesSYM;
			}
#line 3562 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 233: /* assign2: becplusSYM  */
#line 1331 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=becplusSYM;
			}
#line 3570 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 234: /* assign2: becminusSYM  */
#line 1335 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=becminusSYM;
			}
#line 3578 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 235: /* label_stat: idSYM colonSYM  */
#line 1341 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=idSYM;
				(yyval.cl).lc.id=(yyvsp[-1].id);
			}
#line 3587 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 236: /* xid: idSYM  */
#line 1348 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_id(idSYM,(yyvsp[0].id),NULL);
			}
#line 3595 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 237: /* xid: idSYM lparenSYM exp_list rparenSYM  */
#line 1352 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_id(idSYM,(yyvsp[-3].id),(yyvsp[-1].expptr));
			}
#line 3603 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 238: /* xid: idSYM lparenSYM opt_commalist rparenSYM  */
#line 1356 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_array(idSYM,(yyvsp[-3].id),T_ARRAY);
			}
#line 3611 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 241: /* numexp: numexp2  */
#line 1366 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_num((yyvsp[0].exp));
			}
#line 3619 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 242: /* numexp2: numexp2 eqlSYM numexp2  */
#line 1372 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(eqlSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3627 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 243: /* numexp2: numexp2 neqSYM numexp2  */
#line 1376 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(neqSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3635 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 244: /* numexp2: numexp2 lssSYM numexp2  */
#line 1380 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(lssSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3643 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 245: /* numexp2: numexp2 gtrSYM numexp2  */
#line 1384 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(gtrSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3651 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 246: /* numexp2: numexp2 leqSYM numexp2  */
#line 1388 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(leqSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3659 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 247: /* numexp2: numexp2 geqSYM numexp2  */
#line 1392 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(geqSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3667 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 248: /* numexp2: numexp2 andSYM numexp2  */
#line 1396 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(andSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3675 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 249: /* numexp2: numexp2 andthenSYM numexp2  */
#line 1400 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(andthenSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3683 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 250: /* numexp2: numexp2 orSYM numexp2  */
#line 1404 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(orSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3691 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 251: /* numexp2: numexp2 orthenSYM numexp2  */
#line 1408 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(orthenSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3699 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 252: /* numexp2: numexp2 eorSYM numexp2  */
#line 1412 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(eorSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3707 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 253: /* numexp2: numexp2 plusSYM numexp2  */
#line 1416 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(plusSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3715 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 254: /* numexp2: numexp2 minusSYM numexp2  */
#line 1420 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(minusSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3723 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 255: /* numexp2: numexp2 timesSYM numexp2  */
#line 1424 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(timesSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3731 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 256: /* numexp2: numexp2 divideSYM numexp2  */
#line 1428 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(divideSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3739 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 257: /* numexp2: numexp2 powerSYM numexp2  */
#line 1432 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(powerSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3747 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 258: /* numexp2: numexp2 divSYM numexp2  */
#line 1436 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(divSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3755 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 259: /* numexp2: numexp2 modSYM numexp2  */
#line 1440 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(modSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3763 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 260: /* numexp2: stringexp2 eqlSYM stringexp2  */
#line 1444 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(eqlSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3771 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 261: /* numexp2: stringexp2 neqSYM stringexp2  */
#line 1448 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(neqSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3779 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 262: /* numexp2: stringexp2 lssSYM stringexp2  */
#line 1452 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(lssSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3787 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 263: /* numexp2: stringexp2 gtrSYM stringexp2  */
#line 1456 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(gtrSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3795 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 264: /* numexp2: stringexp2 leqSYM stringexp2  */
#line 1460 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(leqSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3803 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 265: /* numexp2: stringexp2 geqSYM stringexp2  */
#line 1464 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(geqSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3811 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 266: /* numexp2: stringexp2 inSYM stringexp2  */
#line 1468 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(inSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3819 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 267: /* numexp2: minusSYM numexp2  */
#line 1472 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary(minusSYM,(yyvsp[0].exp));
			}
#line 3827 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 268: /* numexp2: plusSYM numexp2  */
#line 1476 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary(plusSYM,(yyvsp[0].exp));
			}
#line 3835 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 269: /* numexp2: intnumSYM  */
#line 1480 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_int((yyvsp[0].num));
			}
#line 3843 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 270: /* numexp2: floatnumSYM  */
#line 1484 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_float(&(yyvsp[0].dubbel));
			}
#line 3851 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 272: /* numexp2: tsrnSYM lparenSYM stringexp2 rparenSYM  */
#line 1489 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary((yyvsp[-3].inum),(yyvsp[-1].exp));
			}
#line 3859 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 273: /* numexp2: lenSYM lparenSYM stringexp2 rparenSYM  */
#line 1493 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary((yyvsp[-3].inum),(yyvsp[-1].exp));
			}
#line 3867 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 274: /* numexp2: lenSYM lparenSYM numexp2 rparenSYM  */
#line 1497 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary((yyvsp[-3].inum),(yyvsp[-1].exp));
			}
#line 3875 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 275: /* numexp2: tnrnSYM lparenSYM numexp2 rparenSYM  */
#line 1501 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary((yyvsp[-3].inum),(yyvsp[-1].exp));
			}
#line 3883 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 276: /* numexp2: rndSYM  */
#line 1505 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(_RND,NULL,NULL);
			}
#line 3891 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 277: /* numexp2: rndSYM lparenSYM numexp2 rparenSYM  */
#line 1509 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(_RND,NULL,(yyvsp[-1].exp));
			}
#line 3899 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 278: /* numexp2: rndSYM lparenSYM numexp2 commaSYM numexp2 rparenSYM  */
#line 1513 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(_RND,(yyvsp[-3].exp),(yyvsp[-1].exp));
			}
#line 3907 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 279: /* numexp2: rnSYM  */
#line 1517 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_const((yyvsp[0].inum));
			}
#line 3915 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 280: /* numexp2: sysSYM lparenSYM exp_list rparenSYM  */
#line 1521 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_sys(sysSYM,T_SYS,(yyvsp[-1].expptr));
			}
#line 3923 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 281: /* numexp2: lparenSYM numexp2 rparenSYM  */
#line 1525 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary(lparenSYM,(yyvsp[-1].exp));
			}
#line 3931 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 282: /* stringexp: stringexp2  */
#line 1531 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_str((yyvsp[0].exp));
			}
#line 3939 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 283: /* stringexp2: stringexp2 plusSYM string_factor  */
#line 1537 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(plusSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3947 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 285: /* stringexp2: stringexp2 timesSYM numexp2  */
#line 1542 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(timesSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3955 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 287: /* opt_stringexp: %empty  */
#line 1549 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=NULL;
			}
#line 3963 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 289: /* string_factor: string_factor substr_spec  */
#line 1556 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_substr((yyvsp[-1].exp),&(yyvsp[0].twoexp));
			}
#line 3971 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 290: /* string_factor: tnrsSYM lparenSYM numexp2 rparenSYM  */
#line 1560 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary((yyvsp[-3].inum),(yyvsp[-1].exp));
			}
#line 3979 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 291: /* string_factor: tsrsSYM lparenSYM stringexp2 rparenSYM  */
#line 1564 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary((yyvsp[-3].inum),(yyvsp[-1].exp));
			}
#line 3987 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 292: /* string_factor: rsSYM  */
#line 1568 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_const((yyvsp[0].inum));
			}
#line 3995 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 293: /* string_factor: tonrsSYM opt_arg  */
#line 1572 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary((yyvsp[-1].inum),(yyvsp[0].exp));
			}
#line 4003 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 294: /* string_factor: stringSYM  */
#line 1576 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_string((yyvsp[0].str));
			}
#line 4011 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 295: /* string_factor: syssSYM lparenSYM exp_list rparenSYM  */
#line 1580 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_sys(syssSYM,T_SYSS,(yyvsp[-1].expptr));
			}
#line 4019 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 296: /* string_factor: tsrsnSYM lparenSYM exp_list rparenSYM  */
#line 1584 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
			(yyval.exp)=pars_exp_sys((yyvsp[-3].inum),T_SYSS,(yyvsp[-1].expptr));
			}
#line 4027 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 297: /* string_factor: lparenSYM stringexp2 rparenSYM  */
#line 1588 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary(lparenSYM,(yyvsp[-1].exp));
			}
#line 4035 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 298: /* opt_arg: lparenSYM numexp2 rparenSYM  */
#line 1594 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=(yyvsp[-1].exp);
			}
#line 4043 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 299: /* opt_arg: %empty  */
#line 1598 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=NULL;
			}
#line 4051 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 300: /* substr_spec: lparenSYM substr_spec2 rparenSYM  */
#line 1604 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp)=(yyvsp[-1].twoexp);
			}
#line 4059 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 301: /* substr_spec2: numexp colonSYM numexp  */
#line 1610 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp).exp1=(yyvsp[-2].exp);
				(yyval.twoexp).exp2=(yyvsp[0].exp);
			}
#line 4068 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 302: /* substr_spec2: colonSYM numexp  */
#line 1615 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp).exp1=NULL;
				(yyval.twoexp).exp2=(yyvsp[0].exp);
			}
#line 4077 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 303: /* substr_spec2: numexp colonSYM  */
#line 1620 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp).exp1=(yyvsp[-1].exp);
				(yyval.twoexp).exp2=NULL;
			}
#line 4086 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 304: /* substr_spec2: colonSYM numexp colonSYM  */
#line 1625 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp).exp1=(yyvsp[-1].exp);
				(yyval.twoexp).exp2=(yyvsp[-1].exp);
			}
#line 4095 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 306: /* optnumlvalue: %empty  */
#line 1633 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=NULL;
			}
#line 4103 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 308: /* optexp: %empty  */
#line 1640 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=NULL;
			}
#line 4111 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 310: /* optid: %empty  */
#line 1647 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.id)=NULL;
			}
#line 4119 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 312: /* optid2: %empty  */
#line 1654 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.id)=NULL;
			}
#line 4127 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 313: /* optfile: file_designator  */
#line 1660 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexpp)=PARS_ALLOC(struct two_exp);
				
				*((yyval.twoexpp))=(yyvsp[0].twoexp);
			}
#line 4137 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 314: /* optfile: %empty  */
#line 1666 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {	
				(yyval.twoexpp)=NULL;
			}
#line 4145 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 317: /* lval_list: lval_list commaSYM lvalue  */
#line 1676 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.expptr)=pars_explist_item((yyvsp[0].exp),(yyvsp[-2].expptr));
			}
#line 4153 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 318: /* lval_list: lvalue  */
#line 1680 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.expptr)=pars_explist_item((yyvsp[0].exp),NULL);
			}
#line 4161 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 321: /* numlvalue: numlvalue2  */
#line 1690 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				if (!exp_list_of_nums((yyvsp[0].exp)->e.expid.exproot))
					pars_error("Indices of numeric lvalue \"%s\" must be numerics",(yyvsp[0].exp)->e.expid.id->name);
			}
#line 4170 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 323: /* numlvalue2: intidSYM  */
#line 1698 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_id(intidSYM,(yyvsp[0].id),NULL);
			}
#line 4178 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 324: /* numlvalue2: intidSYM lparenSYM exp_list rparenSYM  */
#line 1702 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_id(intidSYM,(yyvsp[-3].id),(yyvsp[-1].expptr));
			}
#line 4186 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 325: /* numlvalue2: intidSYM lparenSYM opt_commalist rparenSYM  */
#line 1706 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_array(intidSYM,(yyvsp[-3].id),T_ARRAY);
			}
#line 4194 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 326: /* strlvalue: strlvalue2  */
#line 1712 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				if (!exp_list_of_nums((yyvsp[0].exp)->e.expsid.exproot))
					pars_error("Indices of string lvalue \"%s\" must be numerics",(yyvsp[0].exp)->e.expsid.id->name);
			}
#line 4203 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 327: /* strlvalue2: stringidSYM  */
#line 1719 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_sid((yyvsp[0].id),NULL,NULL);
			}
#line 4211 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 328: /* strlvalue2: stringidSYM lparenSYM exp_list rparenSYM  */
#line 1723 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_sid((yyvsp[-3].id),(yyvsp[-1].expptr),NULL);
			}
#line 4219 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 329: /* strlvalue2: stringidSYM substr_spec  */
#line 1727 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_sid((yyvsp[-1].id),NULL,&(yyvsp[0].twoexp));
			}
#line 4227 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 330: /* strlvalue2: stringidSYM lparenSYM exp_list rparenSYM substr_spec  */
#line 1731 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_sid((yyvsp[-4].id),(yyvsp[-2].expptr),&(yyvsp[0].twoexp));
			}
#line 4235 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 331: /* strlvalue2: stringidSYM lparenSYM opt_commalist rparenSYM  */
#line 1735 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_array(intidSYM,(yyvsp[-3].id),T_SARRAY);
			}
#line 4243 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 332: /* file_designator: fileSYM numexp colonSYM  */
#line 1741 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp).exp1=(yyvsp[-1].exp);
				(yyval.twoexp).exp2=NULL;
			}
#line 4252 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 333: /* file_designator: fileSYM numexp commaSYM numexp colonSYM  */
#line 1746 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp).exp1=(yyvsp[-3].exp);
				(yyval.twoexp).exp2=(yyvsp[-1].exp);
			}
#line 4261 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 334: /* opt_external: externalSYM stringexp  */
#line 1753 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.extptr)=PARS_ALLOC(struct ext_rec);
				
				(yyval.extptr)->dynamic=0;
				(yyval.extptr)->filename=(yyvsp[0].exp);
				(yyval.extptr)->seg=NULL;
			}
#line 4273 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 335: /* opt_external: dynamicSYM externalSYM stringexp  */
#line 1761 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.extptr)=PARS_ALLOC(struct ext_rec);
				
				(yyval.extptr)->dynamic=dynamicSYM;
				(yyval.extptr)->filename=(yyvsp[0].exp);
				(yyval.extptr)->seg=NULL;
			}
#line 4285 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 336: /* opt_external: staticSYM externalSYM stringexp  */
#line 1769 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.extptr)=PARS_ALLOC(struct ext_rec);
				
				(yyval.extptr)->dynamic=staticSYM;
				(yyval.extptr)->filename=(yyvsp[0].exp);
				(yyval.extptr)->seg=NULL;
			}
#line 4297 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 337: /* opt_external: %empty  */
#line 1777 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.extptr)=NULL;
			}
#line 4305 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 338: /* procfunc_head: lparenSYM parmlist rparenSYM  */
#line 1783 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=(yyvsp[-1].parmptr);
			}
#line 4313 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 339: /* procfunc_head: %empty  */
#line 1787 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=NULL;
			}
#line 4321 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 340: /* parmlist: parmlist commaSYM parmitem  */
#line 1793 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=(yyvsp[0].parmptr);
				(yyval.parmptr)->next=(yyvsp[-2].parmptr);
			}
#line 4330 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 341: /* parmlist: parmitem  */
#line 1798 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=(yyvsp[0].parmptr);
				(yyval.parmptr)->next=NULL;
			}
#line 4339 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 342: /* parmitem: oneparm  */
#line 1805 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=PARS_ALLOC(struct parm_list);
				(yyval.parmptr)->id=(yyvsp[0].oneparm).id;
				(yyval.parmptr)->array=(yyvsp[0].oneparm).array;
				(yyval.parmptr)->ref=0;
			}
#line 4350 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 343: /* parmitem: refSYM oneparm  */
#line 1812 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=PARS_ALLOC(struct parm_list);
				(yyval.parmptr)->id=(yyvsp[0].oneparm).id;
				(yyval.parmptr)->array=(yyvsp[0].oneparm).array;
				(yyval.parmptr)->ref=refSYM;
			}
#line 4361 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 344: /* parmitem: nameSYM id  */
#line 1819 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=PARS_ALLOC(struct parm_list);
				(yyval.parmptr)->id=(yyvsp[0].id);
				(yyval.parmptr)->array=0;
				(yyval.parmptr)->ref=nameSYM;
			}
#line 4372 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 345: /* parmitem: procSYM idSYM  */
#line 1826 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=PARS_ALLOC(struct parm_list);
				(yyval.parmptr)->id=(yyvsp[0].id);
				(yyval.parmptr)->array=0;
				(yyval.parmptr)->ref=procSYM;
			}
#line 4383 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 346: /* parmitem: funcSYM id  */
#line 1833 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=PARS_ALLOC(struct parm_list);
				(yyval.parmptr)->id=(yyvsp[0].id);
				(yyval.parmptr)->array=0;
				(yyval.parmptr)->ref=funcSYM;
			}
#line 4394 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 347: /* oneparm: id  */
#line 1842 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.oneparm).id=(yyvsp[0].id);
				(yyval.oneparm).array=0;
			}
#line 4403 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 348: /* oneparm: id lparenSYM opt_commalist rparenSYM  */
#line 1847 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.oneparm).id=(yyvsp[-3].id);
				(yyval.oneparm).array=1;
			}
#line 4412 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 355: /* exp_list: exp_list commaSYM exp  */
#line 1866 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.expptr)=pars_explist_item((yyvsp[0].exp),(yyvsp[-2].expptr));
				}
#line 4420 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 356: /* exp_list: exp  */
#line 1870 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.expptr)=pars_explist_item((yyvsp[0].exp),NULL);
			}
#line 4428 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 357: /* optsimple_stat: simple_stat  */
#line 1876 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				if ((yyvsp[0].cl).cmd<0)
					(yyval.pcl)=NULL;
				else
				{
					(yyval.pcl)=stat_dup(&(yyvsp[0].cl));
					(yyval.pcl)->ld=NULL;
				}
			}
#line 4442 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 358: /* optsimple_stat: %empty  */
#line 1886 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl)=NULL;
			}
#line 4450 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 360: /* optfilename: %empty  */
#line 1893 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.str)=NULL;
			}
#line 4458 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 367: /* optread_only: read_onlySYM  */
#line 1911 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=read_onlySYM;
			}
#line 4466 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 368: /* optread_only: %empty  */
#line 1915 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=0;
			}
#line 4474 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 369: /* optclosed: closedSYM  */
#line 1921 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=closedSYM;
			}
#line 4482 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 370: /* optclosed: %empty  */
#line 1925 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=0;
			}
#line 4490 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;


#line 4494 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.cc"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1930 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"


PRIVATE void p_error(const char *s)
	{
		pars_error((char *)s);
		yyclearin;
	}
	
