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
#line 1 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"

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


#line 113 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"

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
  YYSYMBOL_divideSYM = 22,                 /* divideSYM  */
  YYSYMBOL_divSYM = 23,                    /* divSYM  */
  YYSYMBOL_doSYM = 24,                     /* doSYM  */
  YYSYMBOL_downtoSYM = 25,                 /* downtoSYM  */
  YYSYMBOL_dynamicSYM = 26,                /* dynamicSYM  */
  YYSYMBOL_editSYM = 27,                   /* editSYM  */
  YYSYMBOL_elifSYM = 28,                   /* elifSYM  */
  YYSYMBOL_elseSYM = 29,                   /* elseSYM  */
  YYSYMBOL_endcaseSYM = 30,                /* endcaseSYM  */
  YYSYMBOL_endforSYM = 31,                 /* endforSYM  */
  YYSYMBOL_endfuncSYM = 32,                /* endfuncSYM  */
  YYSYMBOL_endifSYM = 33,                  /* endifSYM  */
  YYSYMBOL_endloopSYM = 34,                /* endloopSYM  */
  YYSYMBOL_endprocSYM = 35,                /* endprocSYM  */
  YYSYMBOL_endSYM = 36,                    /* endSYM  */
  YYSYMBOL_endtrapSYM = 37,                /* endtrapSYM  */
  YYSYMBOL_endwhileSYM = 38,               /* endwhileSYM  */
  YYSYMBOL_envSYM = 39,                    /* envSYM  */
  YYSYMBOL_enterSYM = 40,                  /* enterSYM  */
  YYSYMBOL_eolnSYM = 41,                   /* eolnSYM  */
  YYSYMBOL_eorSYM = 42,                    /* eorSYM  */
  YYSYMBOL_eqlSYM = 43,                    /* eqlSYM  */
  YYSYMBOL_escSYM = 44,                    /* escSYM  */
  YYSYMBOL_execSYM = 45,                   /* execSYM  */
  YYSYMBOL_exitSYM = 46,                   /* exitSYM  */
  YYSYMBOL_externalSYM = 47,               /* externalSYM  */
  YYSYMBOL_fileSYM = 48,                   /* fileSYM  */
  YYSYMBOL_forSYM = 49,                    /* forSYM  */
  YYSYMBOL_funcSYM = 50,                   /* funcSYM  */
  YYSYMBOL_geqSYM = 51,                    /* geqSYM  */
  YYSYMBOL_gtrSYM = 52,                    /* gtrSYM  */
  YYSYMBOL_handlerSYM = 53,                /* handlerSYM  */
  YYSYMBOL_ifSYM = 54,                     /* ifSYM  */
  YYSYMBOL_importSYM = 55,                 /* importSYM  */
  YYSYMBOL_inputSYM = 56,                  /* inputSYM  */
  YYSYMBOL_inSYM = 57,                     /* inSYM  */
  YYSYMBOL_leqSYM = 58,                    /* leqSYM  */
  YYSYMBOL_listSYM = 59,                   /* listSYM  */
  YYSYMBOL_localSYM = 60,                  /* localSYM  */
  YYSYMBOL_loadSYM = 61,                   /* loadSYM  */
  YYSYMBOL_loopSYM = 62,                   /* loopSYM  */
  YYSYMBOL_lparenSYM = 63,                 /* lparenSYM  */
  YYSYMBOL_lssSYM = 64,                    /* lssSYM  */
  YYSYMBOL_minusSYM = 65,                  /* minusSYM  */
  YYSYMBOL_mkdirSYM = 66,                  /* mkdirSYM  */
  YYSYMBOL_modSYM = 67,                    /* modSYM  */
  YYSYMBOL_nameSYM = 68,                   /* nameSYM  */
  YYSYMBOL_neqSYM = 69,                    /* neqSYM  */
  YYSYMBOL_newSYM = 70,                    /* newSYM  */
  YYSYMBOL_nullSYM = 71,                   /* nullSYM  */
  YYSYMBOL_ofSYM = 72,                     /* ofSYM  */
  YYSYMBOL_openSYM = 73,                   /* openSYM  */
  YYSYMBOL_orSYM = 74,                     /* orSYM  */
  YYSYMBOL_orthenSYM = 75,                 /* orthenSYM  */
  YYSYMBOL_osSYM = 76,                     /* osSYM  */
  YYSYMBOL_otherwiseSYM = 77,              /* otherwiseSYM  */
  YYSYMBOL_pageSYM = 78,                   /* pageSYM  */
  YYSYMBOL_plusSYM = 79,                   /* plusSYM  */
  YYSYMBOL_powerSYM = 80,                  /* powerSYM  */
  YYSYMBOL_printSYM = 81,                  /* printSYM  */
  YYSYMBOL_procSYM = 82,                   /* procSYM  */
  YYSYMBOL_quitSYM = 83,                   /* quitSYM  */
  YYSYMBOL_randomSYM = 84,                 /* randomSYM  */
  YYSYMBOL_readSYM = 85,                   /* readSYM  */
  YYSYMBOL_read_onlySYM = 86,              /* read_onlySYM  */
  YYSYMBOL_refSYM = 87,                    /* refSYM  */
  YYSYMBOL_renumberSYM = 88,               /* renumberSYM  */
  YYSYMBOL_repeatSYM = 89,                 /* repeatSYM  */
  YYSYMBOL_restoreSYM = 90,                /* restoreSYM  */
  YYSYMBOL_retrySYM = 91,                  /* retrySYM  */
  YYSYMBOL_returnSYM = 92,                 /* returnSYM  */
  YYSYMBOL_rmdirSYM = 93,                  /* rmdirSYM  */
  YYSYMBOL_rndSYM = 94,                    /* rndSYM  */
  YYSYMBOL_rparenSYM = 95,                 /* rparenSYM  */
  YYSYMBOL_runSYM = 96,                    /* runSYM  */
  YYSYMBOL_saveSYM = 97,                   /* saveSYM  */
  YYSYMBOL_scanSYM = 98,                   /* scanSYM  */
  YYSYMBOL_select_inputSYM = 99,           /* select_inputSYM  */
  YYSYMBOL_select_outputSYM = 100,         /* select_outputSYM  */
  YYSYMBOL_semicolonSYM = 101,             /* semicolonSYM  */
  YYSYMBOL_staticSYM = 102,                /* staticSYM  */
  YYSYMBOL_stepSYM = 103,                  /* stepSYM  */
  YYSYMBOL_stopSYM = 104,                  /* stopSYM  */
  YYSYMBOL_sysSYM = 105,                   /* sysSYM  */
  YYSYMBOL_syssSYM = 106,                  /* syssSYM  */
  YYSYMBOL_thenSYM = 107,                  /* thenSYM  */
  YYSYMBOL_timesSYM = 108,                 /* timesSYM  */
  YYSYMBOL_toSYM = 109,                    /* toSYM  */
  YYSYMBOL_traceSYM = 110,                 /* traceSYM  */
  YYSYMBOL_trapSYM = 111,                  /* trapSYM  */
  YYSYMBOL_unitSYM = 112,                  /* unitSYM  */
  YYSYMBOL_untilSYM = 113,                 /* untilSYM  */
  YYSYMBOL_usingSYM = 114,                 /* usingSYM  */
  YYSYMBOL_whenSYM = 115,                  /* whenSYM  */
  YYSYMBOL_whileSYM = 116,                 /* whileSYM  */
  YYSYMBOL_writeSYM = 117,                 /* writeSYM  */
  YYSYMBOL_rnSYM = 118,                    /* rnSYM  */
  YYSYMBOL_rsSYM = 119,                    /* rsSYM  */
  YYSYMBOL_tnrnSYM = 120,                  /* tnrnSYM  */
  YYSYMBOL_tnrsSYM = 121,                  /* tnrsSYM  */
  YYSYMBOL_tsrnSYM = 122,                  /* tsrnSYM  */
  YYSYMBOL_tonrsSYM = 123,                 /* tonrsSYM  */
  YYSYMBOL_tsrsSYM = 124,                  /* tsrsSYM  */
  YYSYMBOL_tsrsnSYM = 125,                 /* tsrsnSYM  */
  YYSYMBOL_floatnumSYM = 126,              /* floatnumSYM  */
  YYSYMBOL_idSYM = 127,                    /* idSYM  */
  YYSYMBOL_intidSYM = 128,                 /* intidSYM  */
  YYSYMBOL_stringidSYM = 129,              /* stringidSYM  */
  YYSYMBOL_intnumSYM = 130,                /* intnumSYM  */
  YYSYMBOL_remSYM = 131,                   /* remSYM  */
  YYSYMBOL_stringSYM = 132,                /* stringSYM  */
  YYSYMBOL_USIGN = 133,                    /* USIGN  */
  YYSYMBOL_YYACCEPT = 134,                 /* $accept  */
  YYSYMBOL_a_comal_line = 135,             /* a_comal_line  */
  YYSYMBOL_comal_line = 136,               /* comal_line  */
  YYSYMBOL_optrem = 137,                   /* optrem  */
  YYSYMBOL_command = 138,                  /* command  */
  YYSYMBOL_list_cmd = 139,                 /* list_cmd  */
  YYSYMBOL_line_range = 140,               /* line_range  */
  YYSYMBOL_renumlines = 141,               /* renumlines  */
  YYSYMBOL_autolines = 142,                /* autolines  */
  YYSYMBOL_program_line = 143,             /* program_line  */
  YYSYMBOL_complex_stat = 144,             /* complex_stat  */
  YYSYMBOL_simple_stat = 145,              /* simple_stat  */
  YYSYMBOL_complex_1word = 146,            /* complex_1word  */
  YYSYMBOL_simple_1word = 147,             /* simple_1word  */
  YYSYMBOL_case_stat = 148,                /* case_stat  */
  YYSYMBOL_close_stat = 149,               /* close_stat  */
  YYSYMBOL_cursor_stat = 150,              /* cursor_stat  */
  YYSYMBOL_chdir_stat = 151,               /* chdir_stat  */
  YYSYMBOL_rmdir_stat = 152,               /* rmdir_stat  */
  YYSYMBOL_mkdir_stat = 153,               /* mkdir_stat  */
  YYSYMBOL_data_stat = 154,                /* data_stat  */
  YYSYMBOL_del_stat = 155,                 /* del_stat  */
  YYSYMBOL_dir_stat = 156,                 /* dir_stat  */
  YYSYMBOL_unit_stat = 157,                /* unit_stat  */
  YYSYMBOL_local_stat = 158,               /* local_stat  */
  YYSYMBOL_local_list = 159,               /* local_list  */
  YYSYMBOL_local_item = 160,               /* local_item  */
  YYSYMBOL_dim_stat = 161,                 /* dim_stat  */
  YYSYMBOL_dim_list = 162,                 /* dim_list  */
  YYSYMBOL_dim_item = 163,                 /* dim_item  */
  YYSYMBOL_of = 164,                       /* of  */
  YYSYMBOL_opt_dim_ensions = 165,          /* opt_dim_ensions  */
  YYSYMBOL_dim_ensions = 166,              /* dim_ensions  */
  YYSYMBOL_dim_ension_list = 167,          /* dim_ension_list  */
  YYSYMBOL_dim_ension = 168,               /* dim_ension  */
  YYSYMBOL_elif_stat = 169,                /* elif_stat  */
  YYSYMBOL_exit_stat = 170,                /* exit_stat  */
  YYSYMBOL_ifwhen = 171,                   /* ifwhen  */
  YYSYMBOL_exec_stat = 172,                /* exec_stat  */
  YYSYMBOL_for_stat = 173,                 /* for_stat  */
  YYSYMBOL_todownto = 174,                 /* todownto  */
  YYSYMBOL_optstep = 175,                  /* optstep  */
  YYSYMBOL_func_stat = 176,                /* func_stat  */
  YYSYMBOL_if_stat = 177,                  /* if_stat  */
  YYSYMBOL_import_stat = 178,              /* import_stat  */
  YYSYMBOL_import_list = 179,              /* import_list  */
  YYSYMBOL_input_stat = 180,               /* input_stat  */
  YYSYMBOL_input_modifier = 181,           /* input_modifier  */
  YYSYMBOL_open_stat = 182,                /* open_stat  */
  YYSYMBOL_open_type = 183,                /* open_type  */
  YYSYMBOL_os_stat = 184,                  /* os_stat  */
  YYSYMBOL_print_stat = 185,               /* print_stat  */
  YYSYMBOL_printi = 186,                   /* printi  */
  YYSYMBOL_prnum_list = 187,               /* prnum_list  */
  YYSYMBOL_print_list = 188,               /* print_list  */
  YYSYMBOL_pr_sep = 189,                   /* pr_sep  */
  YYSYMBOL_optpr_sep = 190,                /* optpr_sep  */
  YYSYMBOL_proc_stat = 191,                /* proc_stat  */
  YYSYMBOL_read_stat = 192,                /* read_stat  */
  YYSYMBOL_restore_stat = 193,             /* restore_stat  */
  YYSYMBOL_return_stat = 194,              /* return_stat  */
  YYSYMBOL_run_stat = 195,                 /* run_stat  */
  YYSYMBOL_select_out_stat = 196,          /* select_out_stat  */
  YYSYMBOL_select_in_stat = 197,           /* select_in_stat  */
  YYSYMBOL_stop_stat = 198,                /* stop_stat  */
  YYSYMBOL_sys_stat = 199,                 /* sys_stat  */
  YYSYMBOL_until_stat = 200,               /* until_stat  */
  YYSYMBOL_trace_stat = 201,               /* trace_stat  */
  YYSYMBOL_trap_stat = 202,                /* trap_stat  */
  YYSYMBOL_plusorminus = 203,              /* plusorminus  */
  YYSYMBOL_when_stat = 204,                /* when_stat  */
  YYSYMBOL_when_list = 205,                /* when_list  */
  YYSYMBOL_when_numlist = 206,             /* when_numlist  */
  YYSYMBOL_when_numitem = 207,             /* when_numitem  */
  YYSYMBOL_when_strlist = 208,             /* when_strlist  */
  YYSYMBOL_when_stritem = 209,             /* when_stritem  */
  YYSYMBOL_relop = 210,                    /* relop  */
  YYSYMBOL_while_stat = 211,               /* while_stat  */
  YYSYMBOL_repeat_stat = 212,              /* repeat_stat  */
  YYSYMBOL_write_stat = 213,               /* write_stat  */
  YYSYMBOL_assign_stat = 214,              /* assign_stat  */
  YYSYMBOL_assign_list = 215,              /* assign_list  */
  YYSYMBOL_assign_item = 216,              /* assign_item  */
  YYSYMBOL_nassign = 217,                  /* nassign  */
  YYSYMBOL_sassign = 218,                  /* sassign  */
  YYSYMBOL_assign1 = 219,                  /* assign1  */
  YYSYMBOL_assign2 = 220,                  /* assign2  */
  YYSYMBOL_label_stat = 221,               /* label_stat  */
  YYSYMBOL_xid = 222,                      /* xid  */
  YYSYMBOL_exp = 223,                      /* exp  */
  YYSYMBOL_numexp = 224,                   /* numexp  */
  YYSYMBOL_numexp2 = 225,                  /* numexp2  */
  YYSYMBOL_stringexp = 226,                /* stringexp  */
  YYSYMBOL_stringexp2 = 227,               /* stringexp2  */
  YYSYMBOL_opt_stringexp = 228,            /* opt_stringexp  */
  YYSYMBOL_string_factor = 229,            /* string_factor  */
  YYSYMBOL_opt_arg = 230,                  /* opt_arg  */
  YYSYMBOL_substr_spec = 231,              /* substr_spec  */
  YYSYMBOL_substr_spec2 = 232,             /* substr_spec2  */
  YYSYMBOL_optnumlvalue = 233,             /* optnumlvalue  */
  YYSYMBOL_optexp = 234,                   /* optexp  */
  YYSYMBOL_optid = 235,                    /* optid  */
  YYSYMBOL_optid2 = 236,                   /* optid2  */
  YYSYMBOL_optfile = 237,                  /* optfile  */
  YYSYMBOL_optfileS = 238,                 /* optfileS  */
  YYSYMBOL_lval_list = 239,                /* lval_list  */
  YYSYMBOL_lvalue = 240,                   /* lvalue  */
  YYSYMBOL_numlvalue = 241,                /* numlvalue  */
  YYSYMBOL_numlvalue2 = 242,               /* numlvalue2  */
  YYSYMBOL_strlvalue = 243,                /* strlvalue  */
  YYSYMBOL_strlvalue2 = 244,               /* strlvalue2  */
  YYSYMBOL_file_designator = 245,          /* file_designator  */
  YYSYMBOL_opt_external = 246,             /* opt_external  */
  YYSYMBOL_procfunc_head = 247,            /* procfunc_head  */
  YYSYMBOL_parmlist = 248,                 /* parmlist  */
  YYSYMBOL_parmitem = 249,                 /* parmitem  */
  YYSYMBOL_oneparm = 250,                  /* oneparm  */
  YYSYMBOL_id = 251,                       /* id  */
  YYSYMBOL_numid = 252,                    /* numid  */
  YYSYMBOL_opt_commalist = 253,            /* opt_commalist  */
  YYSYMBOL_exp_list = 254,                 /* exp_list  */
  YYSYMBOL_optsimple_stat = 255,           /* optsimple_stat  */
  YYSYMBOL_optfilename = 256,              /* optfilename  */
  YYSYMBOL_optof = 257,                    /* optof  */
  YYSYMBOL_optdo = 258,                    /* optdo  */
  YYSYMBOL_optthen = 259,                  /* optthen  */
  YYSYMBOL_optread_only = 260,             /* optread_only  */
  YYSYMBOL_optclosed = 261                 /* optclosed  */
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
#define YYFINAL  238
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1619

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  134
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  128
/* YYNRULES -- Number of rules.  */
#define YYNRULES  365
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  572

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   388


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
     125,   126,   127,   128,   129,   130,   131,   132,   133
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   241,   241,   246,   255,   260,   268,   273,   279,   281,
     287,   291,   292,   297,   302,   307,   312,   317,   321,   325,
     330,   334,   339,   344,   351,   358,   366,   373,   379,   388,
     391,   395,   399,   403,   409,   413,   417,   422,   427,   431,
     435,   441,   447,   448,   450,   455,   456,   457,   458,   459,
     460,   461,   462,   463,   464,   465,   466,   467,   468,   471,
     472,   473,   474,   475,   476,   477,   478,   479,   480,   481,
     482,   483,   484,   485,   486,   487,   488,   489,   490,   491,
     492,   493,   494,   495,   496,   497,   498,   503,   504,   507,
     511,   515,   519,   523,   527,   531,   535,   539,   543,   547,
     553,   558,   562,   568,   572,   576,   581,   585,   591,   598,
     603,   610,   618,   625,   632,   639,   646,   653,   660,   668,
     674,   679,   686,   690,   694,   698,   702,   709,   716,   721,
     728,   732,   736,   740,   746,   747,   750,   752,   757,   763,
     768,   775,   781,   787,   795,   802,   809,   810,   813,   820,
     832,   836,   842,   847,   852,   862,   870,   876,   884,   891,
     900,   908,   914,   921,   926,   935,   939,   943,   947,   955,
     962,   969,   976,   985,   996,   997,  1000,  1004,  1010,  1014,
    1020,  1024,  1030,  1032,  1037,  1047,  1055,  1062,  1069,  1076,
    1084,  1091,  1098,  1105,  1112,  1124,  1131,  1135,  1141,  1148,
    1149,  1152,  1157,  1160,  1164,  1170,  1175,  1178,  1182,  1186,
    1192,  1196,  1200,  1204,  1208,  1212,  1218,  1226,  1234,  1242,
    1249,  1254,  1260,  1264,  1270,  1271,  1274,  1275,  1281,  1285,
    1291,  1295,  1301,  1308,  1312,  1316,  1322,  1323,  1326,  1332,
    1336,  1340,  1344,  1348,  1352,  1356,  1360,  1364,  1368,  1372,
    1376,  1380,  1384,  1388,  1392,  1396,  1400,  1404,  1408,  1412,
    1416,  1420,  1424,  1428,  1432,  1436,  1440,  1444,  1448,  1449,
    1453,  1457,  1461,  1465,  1469,  1473,  1477,  1483,  1489,  1493,
    1494,  1500,  1502,  1507,  1508,  1512,  1516,  1520,  1524,  1528,
    1532,  1536,  1540,  1546,  1551,  1556,  1562,  1567,  1572,  1577,
    1584,  1586,  1591,  1593,  1598,  1600,  1605,  1607,  1612,  1619,
    1624,  1625,  1628,  1632,  1638,  1639,  1642,  1649,  1650,  1654,
    1658,  1664,  1671,  1675,  1679,  1683,  1687,  1693,  1698,  1705,
    1713,  1721,  1730,  1735,  1740,  1745,  1750,  1757,  1764,  1771,
    1778,  1785,  1794,  1799,  1806,  1807,  1810,  1811,  1814,  1815,
    1818,  1822,  1828,  1839,  1844,  1846,  1851,  1852,  1855,  1856,
    1859,  1860,  1863,  1868,  1873,  1878
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
  "divideSYM", "divSYM", "doSYM", "downtoSYM", "dynamicSYM", "editSYM",
  "elifSYM", "elseSYM", "endcaseSYM", "endforSYM", "endfuncSYM",
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
  "floatnumSYM", "idSYM", "intidSYM", "stringidSYM", "intnumSYM", "remSYM",
  "stringSYM", "USIGN", "$accept", "a_comal_line", "comal_line", "optrem",
  "command", "list_cmd", "line_range", "renumlines", "autolines",
  "program_line", "complex_stat", "simple_stat", "complex_1word",
  "simple_1word", "case_stat", "close_stat", "cursor_stat", "chdir_stat",
  "rmdir_stat", "mkdir_stat", "data_stat", "del_stat", "dir_stat",
  "unit_stat", "local_stat", "local_list", "local_item", "dim_stat",
  "dim_list", "dim_item", "of", "opt_dim_ensions", "dim_ensions",
  "dim_ension_list", "dim_ension", "elif_stat", "exit_stat", "ifwhen",
  "exec_stat", "for_stat", "todownto", "optstep", "func_stat", "if_stat",
  "import_stat", "import_list", "input_stat", "input_modifier",
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

#define YYPACT_NINF (-451)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-110)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     637,    12,    -4,   399,    -9,  -451,  1487,   345,   124,   399,
     -25,  -451,   -43,   -41,    34,  -451,   146,   -14,    98,   153,
     -29,   399,  -451,  -451,   117,   399,  -451,  -451,  -451,   122,
      11,   -43,  -451,  1487,   399,   399,   -29,  -451,   399,   399,
    -451,  1487,  1487,  1487,   134,   399,   122,   139,   142,   149,
     759,  -451,   232,   192,  -451,  -451,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,  1450,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,   133,  -451,
     -12,   168,  -451,   102,  -451,  -451,   108,   220,  -451,   399,
     176,  -451,   178,   179,   184,   185,  -451,  -451,    81,   191,
    -451,  -451,  1487,  1487,  1487,  1487,   197,   204,  -451,   205,
     208,  -451,  -451,  -451,   240,  1306,   852,  -451,   148,   211,
    -451,  -451,  -451,  -451,    87,   271,  -451,   224,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,   273,  -451,    48,  -451,
    1487,   276,   156,  -451,  -451,   280,   281,   111,   282,  -451,
     224,  -451,  -451,  -451,  1487,  -451,   156,  -451,   182,   283,
    -451,  -451,  -451,  -451,  -451,   852,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,   293,  -451,     8,  -451,  1487,  1487,
    1487,   277,  -451,  1487,  1487,   399,  1487,  -451,  -451,    -3,
     146,  -451,  -451,   -43,  -451,  -451,    -7,    -3,   146,  -451,
    1487,  -451,  -451,   188,   872,   399,   134,  1487,  1325,  1487,
      68,   187,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
     399,    20,  -451,  1487,   156,  -451,  -451,  -451,  -451,  1487,
    -451,  -451,  -451,   399,  -451,  -451,   186,    93,  1487,  1487,
    1487,  -451,   399,  1487,   399,  1487,   277,  -451,   293,  1011,
     500,  -451,  -451,  1487,  1487,  1487,   399,  1487,  1487,  1487,
    1487,  1487,  1487,  1487,  1487,  1487,  1487,  1487,  1487,  1487,
    1487,  1487,  1487,  1487,  1487,  1487,   399,   399,   399,   399,
     399,   399,   399,  -451,   189,  1487,  1487,     9,   124,  -451,
     146,   146,  -451,   167,  -451,   305,  -451,  -451,  -451,   193,
     194,  1487,     9,   153,  -451,  -451,   308,   305,  -451,   200,
    1487,  -451,  -451,  -451,   293,    28,    39,    41,    43,  1487,
     310,   236,    45,    51,   255,   293,   225,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  1487,   106,   275,   225,   275,   223,
    -451,  -451,  -451,  -451,   399,  -451,  -451,  -451,  -451,   326,
    -451,   328,  -451,  1487,  -451,  -451,   320,  -451,  -451,   333,
    -451,  -451,  1487,  -451,    20,  -451,  -451,  -451,  -451,  -451,
      52,  1070,  1129,   105,    53,   191,   268,   310,  -451,   952,
      56,  1188,   129,  -451,   270,   270,   268,   268,   270,    63,
      63,    63,    63,    63,    47,   268,    63,   270,   270,    47,
     268,   268,    81,    81,    81,  -451,    81,    81,    81,  -451,
      59,  -451,   123,  -451,  -451,  -451,  1487,  -451,  -451,   288,
     273,    61,  -451,  1487,   156,  -451,  -451,  -451,  1487,  -451,
     399,  -451,  -451,  -451,  -451,  -451,  -451,  -451,   338,  1487,
    -451,  -451,   191,  -451,  -451,  -451,  -451,  -451,  1487,   135,
     341,   872,   341,  1487,  -451,  1413,   317,  -451,  -451,  -451,
     872,  1487,  -451,  1487,  -451,  -451,  -451,  -451,  -451,  1487,
    -451,  -451,  -451,  -451,  1487,  -451,  1487,  1487,  -451,  -451,
     340,  -451,  -451,   343,  -451,  -451,  -451,    24,   146,   146,
     228,   146,    62,  -451,  -451,  -451,    33,  -451,  -451,    33,
    -451,  -451,  1487,  -451,   399,  -451,    20,  -451,  1247,  -451,
    -451,  -451,  -451,    22,  -451,  -451,  1487,  -451,  -451,  -451,
    -451,   135,  -451,   312,   399,   316,  -451,  -451,  1487,  -451,
    -451,  -451,  1487,  -451,  -451,  -451,   254,  -451,   399,  -451,
     399,  -451,   278,  1487,   320,  -451,  -451,  -451,  -451,  -451,
     872,  -451
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,     0,    41,     0,   311,    20,     0,    29,     0,   282,
      29,   104,   307,     0,     0,   105,     0,   163,    29,     0,
     355,     0,    17,   103,     0,     0,   106,   174,    10,   309,
      37,   307,   107,   303,     0,    16,   355,    18,     0,     0,
     175,   303,     0,     0,     0,     0,     0,   233,   318,   322,
      44,     8,     0,     0,     7,     4,    11,     6,    88,    59,
      61,    60,    76,    69,    62,    64,    84,    65,    63,    66,
      67,    68,    70,    71,    72,   170,    73,    74,    75,    77,
      78,    79,    80,    81,    82,    83,    85,    87,   219,   221,
     317,     0,   316,     0,   321,     3,     0,    38,    19,     0,
       0,   287,     0,   294,     0,     0,   289,   112,   277,   279,
     283,   310,     0,     0,     0,     0,   271,     0,   274,     0,
       0,   267,   266,   317,     0,   238,     0,   268,     0,    30,
      21,   116,   346,   347,     0,   127,   129,     0,   281,   117,
      22,   306,    15,    14,   148,   345,   157,   159,   342,   344,
       0,     0,     0,   161,    25,    24,    27,   123,   119,   121,
     137,   354,    13,   114,     0,   169,     0,   308,     0,    34,
      23,   186,   302,   236,   237,   277,   187,   113,   188,    12,
     190,   189,   191,   351,   192,   194,     0,   118,     0,   349,
     349,   349,   324,     0,     0,     0,     0,    89,    90,   301,
     305,    92,    94,   307,   102,    96,   105,     0,     0,   101,
       0,    93,    98,     0,    99,     0,   100,     0,     0,     0,
     233,     9,    42,    43,    58,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,     1,     2,
       0,   183,   179,     0,     0,   229,   230,   231,   228,     0,
     224,   225,   227,     0,   226,    40,     0,     0,     0,     0,
       0,   288,     0,     0,     0,     0,     0,   284,   110,     0,
       0,   264,   265,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    31,    32,     0,     0,   133,     0,   130,
       0,     0,   349,     0,   162,   160,   313,   314,   315,     0,
       0,     0,   126,     0,   122,   136,     0,   185,    36,     0,
       0,   197,   196,   195,   218,     0,     0,     0,     0,     0,
     236,     0,     0,     0,   357,   115,   361,    97,   300,    91,
     304,    95,   146,   147,     0,     0,   334,   361,   334,     0,
     193,   212,   214,   210,     0,   215,   211,   213,   198,   199,
     202,   200,   206,     0,   204,   208,   359,   232,     5,     0,
     180,   181,   182,   171,   173,   220,   222,   223,    39,   292,
       0,     0,     0,     0,     0,   278,   280,     0,   276,     0,
       0,     0,     0,   111,   245,   246,   253,   255,   249,   239,
     244,   242,   243,   241,   251,   256,   240,   247,   248,   250,
     254,   252,   257,   262,   260,   263,   261,   259,   258,    33,
       0,   140,   141,   131,   134,   135,     0,   128,   158,   342,
     156,     0,   327,     0,     0,    26,    28,   124,     0,   120,
       0,    35,   350,   348,   235,   234,   320,   319,   297,   298,
     295,   326,   323,   356,   108,   360,   144,   145,     0,     0,
     365,   353,   365,     0,   209,     0,     0,   203,   207,   358,
     353,     0,   178,     0,   290,   285,   293,   286,   291,     0,
     272,   275,   270,   269,     0,   138,     0,     0,   132,   343,
       0,   312,   125,     0,   299,   296,   325,     0,     0,     0,
       0,     0,     0,   336,   337,   364,   332,   352,   155,   332,
     217,   201,     0,   205,     0,   216,   183,   177,     0,   139,
     143,   142,   328,     0,   151,   150,     0,   341,   339,   340,
     338,     0,   333,     0,     0,     0,   154,   184,   182,   172,
     273,   167,     0,   165,   166,   164,   153,   335,     0,   329,
       0,   176,   363,     0,   359,   330,   331,   362,   168,   152,
     353,   149
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -451,  -451,  -451,   144,  -451,  -451,    80,  -451,  -451,  -451,
    -451,    15,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,    50,  -451,  -451,    58,
      55,  -451,    49,  -451,  -124,  -451,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,    73,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,   145,  -364,  -154,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,   -88,  -451,   -87,  -256,  -451,  -451,  -451,
    -451,  -451,   147,  -451,  -451,   -85,  -451,  -451,     2,   -20,
      40,   342,    54,     3,  -451,   126,  -451,   -45,  -451,  -451,
     351,  -451,   -24,  -451,  -451,   227,   -33,  -135,     0,  -133,
       1,    83,  -107,    57,  -451,  -127,  -301,   -13,     6,  -168,
     -94,  -450,   380,  -451,  -145,    64,  -451,   -52
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    52,    53,    54,    55,    56,   130,   170,    98,   221,
     222,   517,   224,    58,   225,    59,    60,    61,    62,    63,
     226,    64,    65,    66,    67,   158,   159,    68,   135,   136,
     436,   324,   307,   430,   431,   227,   228,   354,    69,   229,
     536,   564,   230,   231,    70,   146,    71,   152,    72,   555,
      73,    74,    75,   526,   241,   382,   383,   232,    76,    77,
      78,    79,    80,    81,    82,    83,   233,    84,    85,   333,
     234,   368,   369,   370,   371,   372,   373,   235,   236,    86,
      87,    88,    89,   249,   253,   250,   251,   237,   123,   183,
     173,   125,   174,   126,   139,   109,   261,   267,   341,   347,
     176,   349,   142,   166,   112,   315,   316,    91,   127,    93,
     110,   153,   546,   470,   512,   513,   147,   439,   149,   335,
     184,   518,   162,   464,   480,   466,   568,   516
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      92,    94,    90,   148,   192,   156,   108,   171,   254,   438,
     108,    96,   108,   172,   137,    57,   144,   317,   268,   318,
     483,   172,   337,   342,   108,   160,   168,   551,   108,   -86,
     525,   317,  -109,   318,   150,   380,   175,   108,   108,   111,
     128,   108,   108,   453,   175,   175,   124,   352,   108,   534,
      92,    94,    90,    95,   330,   242,   453,   107,   330,   543,
     453,   131,   311,   138,   348,   223,   330,   330,   330,   280,
     281,   330,   355,   331,   494,   163,   453,   541,   175,   165,
     544,   434,   377,   185,   141,   280,   281,   332,   177,   178,
     140,   143,   180,   181,   334,   336,   338,   343,   155,   187,
     345,   -86,   257,   161,  -109,   129,   552,   553,   353,   245,
     252,   312,   167,   245,   289,   175,   270,   435,   151,   -86,
     571,   381,  -109,   454,    47,    48,    97,   294,   288,   188,
     289,   189,   496,   535,   455,   545,   456,   497,   457,   554,
     461,   169,   293,   294,   441,   248,   462,   484,   488,   248,
     305,   491,    92,    94,   495,   295,   499,   542,   243,   306,
     264,    47,   548,   128,   390,   164,    92,    94,   514,   394,
     150,   295,   264,   344,   305,   245,   246,   247,   186,   351,
     400,   442,   443,   321,   264,   508,   309,   350,   389,   265,
     313,   175,   175,   175,   175,   356,   175,   175,   108,    92,
     487,   265,   189,   509,   326,   190,   322,    92,   264,   325,
     540,   248,   191,   265,    92,    94,    90,   510,   108,   522,
     524,   175,   511,   242,   493,   132,   133,   145,   129,   359,
     154,   340,   238,   239,   244,   256,   346,   265,   255,   258,
     514,   259,   260,   108,    92,    94,   175,   262,   263,   131,
     357,   132,   133,   134,   266,   277,   108,   360,   374,   376,
     273,   175,   132,   133,   145,   393,   175,   274,   275,   178,
     468,   276,   375,   132,   133,   145,   304,   175,   303,   402,
     132,   133,   157,    47,    48,    49,   308,   305,   310,   386,
     314,   339,   280,   281,   379,   319,   320,   323,   329,   422,
     423,   424,   425,   426,   427,   428,   397,   387,   330,   317,
     452,   318,   328,   283,   137,   358,   388,   403,    51,   429,
     444,   284,   285,   450,   459,   445,   446,   463,   286,   160,
     451,   460,   465,   175,   287,   288,   473,   289,   469,   290,
     113,   475,   114,   476,   479,   432,   433,   481,   294,   293,
     294,   312,   504,   515,   532,   539,   115,   563,   533,   558,
     361,   447,   482,   560,   567,   378,   437,   108,   362,   363,
     529,   116,   549,   449,   364,   365,   175,   448,   295,   458,
      99,   366,   117,   100,   440,   175,   367,   521,   384,   523,
     395,   385,   182,   327,   467,   118,   101,   119,   102,   120,
     103,   104,   105,   121,    47,    48,    49,   122,    99,   106,
     128,   501,   547,   477,   557,   472,   179,   506,   474,   570,
     519,   471,     0,   100,     0,     0,     0,   478,     0,     0,
       0,     0,     0,     0,     0,     0,   101,     0,   102,     0,
     103,   104,   105,     0,    92,    94,    49,     0,     0,   106,
       0,   100,     0,   108,     0,   269,   271,   272,     0,     0,
       0,     0,    99,   482,   101,     0,   102,     0,   103,   104,
     105,    92,    94,    90,    49,   129,   498,   106,     0,   108,
      92,    94,    90,   500,     0,     0,   175,     0,   502,     0,
       0,     0,     0,     0,     0,   537,   538,     0,     0,   505,
       0,     0,     0,     0,   503,   100,     0,     0,   507,     0,
       0,     0,     0,   520,     0,   374,     0,     0,   101,     0,
     102,   527,   103,   104,   105,     0,     0,   108,    49,     0,
     375,   106,     0,     0,   432,     0,   530,   531,     0,     0,
       0,     0,     0,   296,     0,     0,     0,   108,     0,     0,
       0,   297,   298,     0,     0,     0,     0,   299,   300,     0,
       0,   108,   477,   108,   301,     0,     0,     0,     0,   302,
      92,    94,    90,     0,     0,     0,   556,     0,   478,   264,
       0,     0,     0,     0,     0,     0,     0,     0,   561,     0,
       0,     0,   562,     0,     0,   389,     0,     0,   559,     0,
       0,   391,   392,   569,     0,     0,     0,   396,   265,     0,
       0,     0,   565,     0,   566,   399,     0,   401,     0,     0,
     404,   405,   406,   407,   408,   409,   410,   411,   412,   413,
     414,   415,   416,   417,   418,   419,   420,   421,     1,     0,
       0,     0,     0,     2,     0,     0,     0,     0,     3,     0,
       4,     0,     0,     5,     6,     0,     7,     8,     9,     0,
       0,     0,     0,     0,    10,     0,     0,     0,     0,     0,
       0,     0,     0,    11,     0,     0,    12,    13,    -9,     0,
       0,     0,    14,    15,     0,     0,     0,     0,     0,     0,
       0,     0,    16,    17,     0,     0,    18,    19,    20,     0,
       0,     0,     0,    21,     0,     0,     0,    22,    23,     0,
      24,     0,     0,    25,     0,    26,     0,     0,    27,     0,
      28,     0,    29,     0,     0,    30,     0,    31,    32,    33,
      34,     0,     0,    35,    36,    37,    38,    39,    40,     0,
       0,    41,    42,     0,     0,     0,     0,    43,    44,    45,
       0,     0,     0,     0,    46,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    47,    48,    49,    50,    51,   193,
       3,     0,     4,     0,     0,     0,     6,   194,   195,     8,
       9,     0,     0,     0,     0,     0,     0,   196,   197,   198,
     199,   200,   201,   202,   203,    11,   204,   205,     0,     0,
       0,     0,     0,     0,    14,   206,     0,     0,   207,   208,
       0,     0,   209,   210,    16,    17,     0,     0,     0,    19,
       0,   211,     0,     0,     0,    21,     0,     0,     0,     0,
      23,   528,    24,     0,     0,    25,   212,    26,     0,     0,
      27,   213,     0,     0,    29,     0,     0,     0,   214,    31,
      32,    33,    34,     0,     0,   215,     0,     0,    38,    39,
      40,     0,     0,    41,    42,     0,     0,     0,     0,    43,
     216,    45,   217,     0,   218,   219,    46,     0,     0,     0,
       0,     0,     0,     3,     0,     4,   220,    48,    49,     6,
       0,   195,     8,     9,     0,   296,     0,     0,     0,     0,
       0,     0,     0,   297,   298,     0,     0,     0,    11,   299,
     300,     0,     0,     0,     0,     0,   301,    14,    15,     0,
       0,   302,     0,     0,     0,     0,     0,    16,    17,     0,
       0,   264,    19,     0,     0,     0,     0,     0,    21,     0,
       0,     0,     0,    23,     0,    24,     0,     0,    25,     0,
      26,     0,     0,    27,     0,   278,   279,    29,     0,     0,
     265,     0,    31,    32,    33,    34,     0,   489,   215,     0,
       0,    38,    39,    40,   280,   281,    41,    42,     0,     0,
       0,     0,    43,    44,    45,     0,     0,     0,     0,    46,
       0,     0,     0,     0,   282,   283,     0,     0,     0,    47,
      48,    49,     0,   284,   285,     0,     0,     0,     0,     0,
     286,     0,     0,     0,   278,   279,   287,   288,     0,   289,
       0,   290,     0,     0,     0,     0,   291,   292,     0,     0,
       0,   293,   294,   280,   281,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   490,     0,     0,
       0,     0,     0,   282,   283,     0,     0,     0,     0,     0,
     295,     0,   284,   285,     0,     0,     0,     0,     0,   286,
       0,     0,     0,   278,   279,   287,   288,     0,   289,     0,
     290,     0,     0,     0,     0,   291,   292,     0,     0,     0,
     293,   294,   280,   281,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   398,     0,     0,     0,
       0,     0,   282,   283,     0,     0,     0,     0,     0,   295,
       0,   284,   285,     0,     0,     0,     0,     0,   286,     0,
       0,     0,   278,   279,   287,   288,     0,   289,     0,   290,
       0,     0,     0,     0,   291,   292,     0,     0,     0,   293,
     294,   280,   281,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   485,     0,     0,     0,     0,
       0,   282,   283,     0,     0,     0,     0,     0,   295,     0,
     284,   285,     0,     0,     0,     0,     0,   286,     0,     0,
       0,   278,   279,   287,   288,     0,   289,     0,   290,     0,
       0,     0,     0,   291,   292,     0,     0,     0,   293,   294,
     280,   281,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   486,     0,     0,     0,     0,     0,
     282,   283,     0,     0,     0,     0,     0,   295,     0,   284,
     285,     0,     0,     0,     0,     0,   286,     0,     0,     0,
     278,   279,   287,   288,     0,   289,     0,   290,     0,     0,
       0,     0,   291,   292,     0,     0,     0,   293,   294,   280,
     281,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   492,     0,     0,     0,     0,     0,   282,
     283,     0,     0,     0,     0,     0,   295,     0,   284,   285,
       0,     0,     0,     0,     0,   286,     0,     0,     0,   278,
     279,   287,   288,     0,   289,     0,   290,     0,     0,     0,
       0,   291,   292,     0,     0,     0,   293,   294,   280,   281,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   550,     0,     0,     0,     0,     0,   282,   283,
       0,     0,     0,     0,     0,   295,     0,   284,   285,     0,
       0,     0,     0,     0,   286,     0,     0,     0,   361,     0,
     287,   288,     0,   289,     0,   290,   362,   363,     0,     0,
     291,   292,   364,   365,     0,   293,   294,     0,   113,   366,
     114,     0,     0,     0,   367,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   115,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   295,     0,     0,     0,     0,   116,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     117,   100,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   118,   101,   119,   102,   120,   103,   104,
     105,   121,    47,    48,    49,   122,   361,   106,     0,     0,
       0,     0,     0,     0,   362,   363,     0,     0,     0,     0,
       0,   365,     0,     0,     0,     0,   113,   366,   114,     0,
       0,     0,   367,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   115,     0,     0,     0,     0,     0,   150,     0,
       0,     0,     0,     0,     0,     0,     0,   116,     0,     0,
       0,     0,     0,   113,     0,   114,     0,     0,   117,   100,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   115,
       0,   118,   101,   119,   102,   120,   103,   104,   105,   121,
      47,    48,    49,   122,   116,   106,     0,     0,     0,     0,
     113,     0,   114,     0,     0,   117,   100,     0,     0,     0,
       0,     0,     0,     0,   240,     0,   115,     0,   118,   101,
     119,   102,   120,   103,   104,   105,   121,    47,    48,    49,
     122,   116,   106,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   117,   100,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   118,   101,   119,   102,   120,
     103,   104,   105,   121,    47,    48,    49,   122,     0,   106
};

static const yytype_int16 yycheck[] =
{
       0,     0,     0,    16,    49,    18,     3,    31,    93,   310,
       7,    15,     9,    33,     8,     0,    14,   152,   112,   152,
     384,    41,   190,   191,    21,    19,    15,     5,    25,    41,
     480,   166,    41,   166,    48,    15,    33,    34,    35,    48,
      65,    38,    39,    15,    41,    42,     6,    54,    45,    25,
      50,    50,    50,    41,    15,    75,    15,     3,    15,    26,
      15,     7,    14,     9,   199,    50,    15,    15,    15,    22,
      23,    15,   207,    65,    15,    21,    15,    15,    75,    25,
      47,    72,    14,    43,   127,    22,    23,    79,    34,    35,
      10,   132,    38,    39,   188,   189,   190,   191,    18,    45,
     194,   113,    99,   132,   113,   130,    84,    85,   115,     7,
       8,    63,    29,     7,    67,   112,   113,   108,   132,   131,
     570,   101,   131,    95,   127,   128,   130,    80,    65,    46,
      67,    63,     9,   109,    95,   102,    95,    14,    95,   117,
      95,   130,    79,    80,   312,    43,    95,    95,    95,    43,
      63,    95,   152,   152,    95,   108,    95,    95,    75,    72,
      79,   127,   526,    65,   258,    48,   166,   166,   469,   263,
      48,   108,    79,   193,    63,     7,     8,     9,    44,   203,
     274,    14,    15,    72,    79,    50,   137,   200,    95,   108,
     150,   188,   189,   190,   191,   208,   193,   194,   195,   199,
      95,   108,    63,    68,   164,    63,   157,   207,    79,   160,
     511,    43,    63,   108,   214,   214,   214,    82,   215,   475,
     476,   218,    87,   243,    95,   127,   128,   129,   130,   214,
     132,   191,     0,    41,   101,    15,   196,   108,   130,    63,
     541,    63,    63,   240,   244,   244,   243,    63,    63,   195,
     210,   127,   128,   129,    63,    15,   253,   217,   218,   219,
      63,   258,   127,   128,   129,   262,   263,    63,    63,   215,
     355,    63,   218,   127,   128,   129,    65,   274,   130,   276,
     127,   128,   129,   127,   128,   129,    15,    63,    15,   249,
      14,    14,    22,    23,   240,    15,    15,    15,    15,   296,
     297,   298,   299,   300,   301,   302,   266,   253,    15,   444,
     330,   444,   130,    43,   308,   127,   130,   277,   131,   130,
      15,    51,    52,    15,    14,   132,   132,    72,    58,   323,
     130,    95,   107,   330,    64,    65,   113,    67,    63,    69,
      63,    15,    65,    15,    24,   305,   306,    14,    80,    79,
      80,    63,    14,    12,    14,   127,    79,   103,    15,    47,
      43,   321,   382,    47,    86,   221,   308,   364,    51,    52,
     494,    94,   526,   323,    57,    58,   373,   322,   108,   339,
      63,    64,   105,   106,   311,   382,    69,   475,   243,   476,
     264,   244,    41,   166,   354,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,    63,   132,
      65,   444,   519,   373,   541,   358,    36,   462,   364,   564,
     472,   357,    -1,   106,    -1,    -1,    -1,   373,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   119,    -1,   121,    -1,
     123,   124,   125,    -1,   444,   444,   129,    -1,    -1,   132,
      -1,   106,    -1,   450,    -1,   113,   114,   115,    -1,    -1,
      -1,    -1,    63,   483,   119,    -1,   121,    -1,   123,   124,
     125,   471,   471,   471,   129,   130,   436,   132,    -1,   476,
     480,   480,   480,   443,    -1,    -1,   483,    -1,   448,    -1,
      -1,    -1,    -1,    -1,    -1,   508,   509,    -1,    -1,   459,
      -1,    -1,    -1,    -1,   450,   106,    -1,    -1,   468,    -1,
      -1,    -1,    -1,   473,    -1,   475,    -1,    -1,   119,    -1,
     121,   481,   123,   124,   125,    -1,    -1,   524,   129,    -1,
     476,   132,    -1,    -1,   494,    -1,   496,   497,    -1,    -1,
      -1,    -1,    -1,    43,    -1,    -1,    -1,   544,    -1,    -1,
      -1,    51,    52,    -1,    -1,    -1,    -1,    57,    58,    -1,
      -1,   558,   522,   560,    64,    -1,    -1,    -1,    -1,    69,
     570,   570,   570,    -1,    -1,    -1,   536,    -1,   524,    79,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   548,    -1,
      -1,    -1,   552,    -1,    -1,    95,    -1,    -1,   544,    -1,
      -1,   259,   260,   563,    -1,    -1,    -1,   265,   108,    -1,
      -1,    -1,   558,    -1,   560,   273,    -1,   275,    -1,    -1,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,     1,    -1,
      -1,    -1,    -1,     6,    -1,    -1,    -1,    -1,    11,    -1,
      13,    -1,    -1,    16,    17,    -1,    19,    20,    21,    -1,
      -1,    -1,    -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    -1,    -1,    39,    40,    41,    -1,
      -1,    -1,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    56,    -1,    -1,    59,    60,    61,    -1,
      -1,    -1,    -1,    66,    -1,    -1,    -1,    70,    71,    -1,
      73,    -1,    -1,    76,    -1,    78,    -1,    -1,    81,    -1,
      83,    -1,    85,    -1,    -1,    88,    -1,    90,    91,    92,
      93,    -1,    -1,    96,    97,    98,    99,   100,   101,    -1,
      -1,   104,   105,    -1,    -1,    -1,    -1,   110,   111,   112,
      -1,    -1,    -1,    -1,   117,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   127,   128,   129,   130,   131,    10,
      11,    -1,    13,    -1,    -1,    -1,    17,    18,    19,    20,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    46,    -1,    -1,    49,    50,
      -1,    -1,    53,    54,    55,    56,    -1,    -1,    -1,    60,
      -1,    62,    -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,
      71,   489,    73,    -1,    -1,    76,    77,    78,    -1,    -1,
      81,    82,    -1,    -1,    85,    -1,    -1,    -1,    89,    90,
      91,    92,    93,    -1,    -1,    96,    -1,    -1,    99,   100,
     101,    -1,    -1,   104,   105,    -1,    -1,    -1,    -1,   110,
     111,   112,   113,    -1,   115,   116,   117,    -1,    -1,    -1,
      -1,    -1,    -1,    11,    -1,    13,   127,   128,   129,    17,
      -1,    19,    20,    21,    -1,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    51,    52,    -1,    -1,    -1,    36,    57,
      58,    -1,    -1,    -1,    -1,    -1,    64,    45,    46,    -1,
      -1,    69,    -1,    -1,    -1,    -1,    -1,    55,    56,    -1,
      -1,    79,    60,    -1,    -1,    -1,    -1,    -1,    66,    -1,
      -1,    -1,    -1,    71,    -1,    73,    -1,    -1,    76,    -1,
      78,    -1,    -1,    81,    -1,     3,     4,    85,    -1,    -1,
     108,    -1,    90,    91,    92,    93,    -1,    15,    96,    -1,
      -1,    99,   100,   101,    22,    23,   104,   105,    -1,    -1,
      -1,    -1,   110,   111,   112,    -1,    -1,    -1,    -1,   117,
      -1,    -1,    -1,    -1,    42,    43,    -1,    -1,    -1,   127,
     128,   129,    -1,    51,    52,    -1,    -1,    -1,    -1,    -1,
      58,    -1,    -1,    -1,     3,     4,    64,    65,    -1,    67,
      -1,    69,    -1,    -1,    -1,    -1,    74,    75,    -1,    -1,
      -1,    79,    80,    22,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,    -1,    -1,
      -1,    -1,    -1,    42,    43,    -1,    -1,    -1,    -1,    -1,
     108,    -1,    51,    52,    -1,    -1,    -1,    -1,    -1,    58,
      -1,    -1,    -1,     3,     4,    64,    65,    -1,    67,    -1,
      69,    -1,    -1,    -1,    -1,    74,    75,    -1,    -1,    -1,
      79,    80,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    95,    -1,    -1,    -1,
      -1,    -1,    42,    43,    -1,    -1,    -1,    -1,    -1,   108,
      -1,    51,    52,    -1,    -1,    -1,    -1,    -1,    58,    -1,
      -1,    -1,     3,     4,    64,    65,    -1,    67,    -1,    69,
      -1,    -1,    -1,    -1,    74,    75,    -1,    -1,    -1,    79,
      80,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    95,    -1,    -1,    -1,    -1,
      -1,    42,    43,    -1,    -1,    -1,    -1,    -1,   108,    -1,
      51,    52,    -1,    -1,    -1,    -1,    -1,    58,    -1,    -1,
      -1,     3,     4,    64,    65,    -1,    67,    -1,    69,    -1,
      -1,    -1,    -1,    74,    75,    -1,    -1,    -1,    79,    80,
      22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    95,    -1,    -1,    -1,    -1,    -1,
      42,    43,    -1,    -1,    -1,    -1,    -1,   108,    -1,    51,
      52,    -1,    -1,    -1,    -1,    -1,    58,    -1,    -1,    -1,
       3,     4,    64,    65,    -1,    67,    -1,    69,    -1,    -1,
      -1,    -1,    74,    75,    -1,    -1,    -1,    79,    80,    22,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    95,    -1,    -1,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    -1,   108,    -1,    51,    52,
      -1,    -1,    -1,    -1,    -1,    58,    -1,    -1,    -1,     3,
       4,    64,    65,    -1,    67,    -1,    69,    -1,    -1,    -1,
      -1,    74,    75,    -1,    -1,    -1,    79,    80,    22,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    95,    -1,    -1,    -1,    -1,    -1,    42,    43,
      -1,    -1,    -1,    -1,    -1,   108,    -1,    51,    52,    -1,
      -1,    -1,    -1,    -1,    58,    -1,    -1,    -1,    43,    -1,
      64,    65,    -1,    67,    -1,    69,    51,    52,    -1,    -1,
      74,    75,    57,    58,    -1,    79,    80,    -1,    63,    64,
      65,    -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    79,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   108,    -1,    -1,    -1,    -1,    94,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     105,   106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,    43,   132,    -1,    -1,
      -1,    -1,    -1,    -1,    51,    52,    -1,    -1,    -1,    -1,
      -1,    58,    -1,    -1,    -1,    -1,    63,    64,    65,    -1,
      -1,    -1,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    79,    -1,    -1,    -1,    -1,    -1,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,    -1,    -1,
      -1,    -1,    -1,    63,    -1,    65,    -1,    -1,   105,   106,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,
      -1,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,    94,   132,    -1,    -1,    -1,    -1,
      63,    -1,    65,    -1,    -1,   105,   106,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   114,    -1,    79,    -1,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,    94,   132,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   105,   106,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,    -1,   132
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,     1,     6,    11,    13,    16,    17,    19,    20,    21,
      27,    36,    39,    40,    45,    46,    55,    56,    59,    60,
      61,    66,    70,    71,    73,    76,    78,    81,    83,    85,
      88,    90,    91,    92,    93,    96,    97,    98,    99,   100,
     101,   104,   105,   110,   111,   112,   117,   127,   128,   129,
     130,   131,   135,   136,   137,   138,   139,   145,   147,   149,
     150,   151,   152,   153,   155,   156,   157,   158,   161,   172,
     178,   180,   182,   184,   185,   186,   192,   193,   194,   195,
     196,   197,   198,   199,   201,   202,   213,   214,   215,   216,
     222,   241,   242,   243,   244,    41,    15,   130,   142,    63,
     106,   119,   121,   123,   124,   125,   132,   226,   227,   229,
     244,    48,   238,    63,    65,    79,    94,   105,   118,   120,
     122,   126,   130,   222,   224,   225,   227,   242,    65,   130,
     140,   226,   127,   128,   129,   162,   163,   252,   226,   228,
     140,   127,   236,   132,   222,   129,   179,   250,   251,   252,
      48,   132,   181,   245,   132,   140,   251,   129,   159,   160,
     252,   132,   256,   226,    48,   226,   237,   245,    15,   130,
     141,   236,   223,   224,   226,   227,   234,   226,   226,   256,
     226,   226,   234,   223,   254,   224,    44,   226,   245,    63,
      63,    63,   231,    10,    18,    19,    28,    29,    30,    31,
      32,    33,    34,    35,    37,    38,    46,    49,    50,    53,
      54,    62,    77,    82,    89,    96,   111,   113,   115,   116,
     127,   143,   144,   145,   146,   148,   154,   169,   170,   173,
     176,   177,   191,   200,   204,   211,   212,   221,     0,    41,
     114,   188,   223,   245,   101,     7,     8,     9,    43,   217,
     219,   220,     8,   218,   219,   130,    15,   227,    63,    63,
      63,   230,    63,    63,    79,   108,    63,   231,   254,   225,
     227,   225,   225,    63,    63,    63,    63,    15,     3,     4,
      22,    23,    42,    43,    51,    52,    58,    64,    65,    67,
      69,    74,    75,    79,    80,   108,    43,    51,    52,    57,
      58,    64,    69,   130,    65,    63,    72,   166,    15,   166,
      15,    14,    63,   224,    14,   239,   240,   241,   243,    15,
      15,    72,   166,    15,   165,   166,   224,   239,   130,    15,
      15,    65,    79,   203,   254,   253,   254,   253,   254,    14,
     224,   232,   253,   254,   223,   254,   224,   233,   241,   235,
     251,   236,    54,   115,   171,   241,   251,   224,   127,   145,
     224,    43,    51,    52,    57,    58,    64,    69,   205,   206,
     207,   208,   209,   210,   224,   226,   224,    14,   137,   226,
      15,   101,   189,   190,   188,   216,   224,   226,   130,    95,
     254,   225,   225,   227,   254,   229,   225,   224,    95,   225,
     254,   225,   227,   224,   225,   225,   225,   225,   225,   225,
     225,   225,   225,   225,   225,   225,   225,   225,   225,   225,
     225,   225,   227,   227,   227,   227,   227,   227,   227,   130,
     167,   168,   224,   224,    72,   108,   164,   163,   250,   251,
     179,   253,    14,    15,    15,   132,   132,   224,   164,   160,
      15,   130,   223,    15,    95,    95,    95,    95,   224,    14,
      95,    95,    95,    72,   257,   107,   259,   224,   219,    63,
     247,   259,   247,   113,   226,    15,    15,   224,   226,    24,
     258,    14,   223,   189,    95,    95,    95,    95,    95,    15,
      95,    95,    95,    95,    15,    95,     9,    14,   224,    95,
     224,   240,   224,   226,    14,   224,   231,   224,    50,    68,
      82,    87,   248,   249,   250,    12,   261,   145,   255,   261,
     224,   207,   210,   209,   210,   255,   187,   224,   225,   168,
     224,   224,    14,    15,    25,   109,   174,   251,   251,   127,
     250,    15,    95,    26,    47,   102,   246,   246,   189,   190,
      95,     5,    84,    85,   117,   183,   224,   249,    47,   226,
      47,   224,   224,   103,   175,   226,   226,    86,   260,   224,
     258,   255
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int16 yyr1[] =
{
       0,   134,   135,   135,   136,   136,   136,   136,   137,   137,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   139,   139,   139,   139,   139,   140,
     140,   140,   140,   140,   141,   141,   141,   141,   142,   142,
     142,   142,   143,   143,   143,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   147,   147,   147,   147,   147,   148,   149,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   159,   160,   160,   160,   160,   160,   161,   162,   162,
     163,   163,   163,   163,   164,   164,   165,   165,   166,   167,
     167,   168,   168,   168,   169,   170,   171,   171,   172,   173,
     174,   174,   175,   175,   176,   177,   178,   178,   179,   179,
     180,   181,   181,   181,   182,   183,   183,   183,   183,   184,
     185,   185,   185,   185,   186,   186,   187,   187,   188,   188,
     189,   189,   190,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   203,   204,   205,
     205,   206,   206,   207,   207,   208,   208,   209,   209,   209,
     210,   210,   210,   210,   210,   210,   211,   212,   213,   214,
     215,   215,   216,   216,   217,   217,   218,   218,   219,   219,
     220,   220,   221,   222,   222,   222,   223,   223,   224,   225,
     225,   225,   225,   225,   225,   225,   225,   225,   225,   225,
     225,   225,   225,   225,   225,   225,   225,   225,   225,   225,
     225,   225,   225,   225,   225,   225,   225,   225,   225,   225,
     225,   225,   225,   225,   225,   225,   225,   226,   227,   227,
     227,   228,   228,   229,   229,   229,   229,   229,   229,   229,
     229,   229,   229,   230,   230,   231,   232,   232,   232,   232,
     233,   233,   234,   234,   235,   235,   236,   236,   237,   237,
     238,   238,   239,   239,   240,   240,   241,   242,   242,   242,
     242,   243,   244,   244,   244,   244,   244,   245,   245,   246,
     246,   246,   246,   247,   247,   248,   248,   249,   249,   249,
     249,   249,   250,   250,   251,   251,   252,   252,   253,   253,
     254,   254,   255,   255,   256,   256,   257,   257,   258,   258,
     259,   259,   260,   260,   261,   261
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     1,     3,     1,     1,     1,     0,
       1,     1,     2,     2,     2,     2,     1,     1,     1,     2,
       1,     2,     2,     2,     2,     2,     4,     2,     4,     0,
       1,     2,     2,     3,     1,     3,     2,     0,     1,     3,
       2,     0,     1,     1,     0,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     2,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       3,     4,     2,     2,     2,     2,     2,     2,     2,     2,
       3,     1,     2,     1,     3,     4,     2,     2,     3,     1,
       2,     3,     4,     2,     1,     1,     1,     0,     3,     3,
       1,     1,     3,     3,     3,     3,     1,     1,     2,     9,
       1,     1,     2,     0,     5,     4,     4,     2,     3,     1,
       3,     1,     2,     0,     7,     1,     1,     1,     3,     2,
       1,     3,     6,     3,     1,     1,     3,     1,     3,     1,
       1,     1,     1,     0,     5,     3,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     3,     1,     1,     2,     1,
       1,     3,     1,     2,     1,     3,     1,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     4,     4,     3,     1,
       3,     1,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     4,     4,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     1,     1,     1,     4,
       4,     1,     4,     6,     1,     4,     3,     1,     3,     1,
       3,     1,     0,     1,     2,     4,     4,     1,     2,     1,
       4,     4,     3,     3,     0,     3,     3,     2,     2,     3,
       1,     0,     1,     0,     1,     0,     1,     0,     1,     0,
       1,     0,     3,     1,     1,     1,     1,     1,     1,     4,
       4,     1,     1,     4,     2,     5,     4,     3,     5,     2,
       3,     3,     0,     3,     0,     3,     1,     1,     2,     2,
       2,     2,     1,     4,     1,     1,     1,     1,     2,     0,
       3,     1,     1,     0,     1,     0,     1,     0,     1,     0,
       1,     0,     1,     0,     1,     0
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
#line 242 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				c_line=(yyvsp[-1].cl);
				YYACCEPT;
			}
#line 2035 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 3: /* a_comal_line: error eolnSYM  */
#line 247 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				p_error("Syntax error");
				yyerrok;
				c_line.cmd=0;
				YYACCEPT;
			}
#line 2046 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 4: /* comal_line: command  */
#line 256 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl)=(yyvsp[0].cl);
				(yyval.cl).ld=NULL;
			}
#line 2055 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 5: /* comal_line: intnumSYM program_line optrem  */
#line 261 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl)=(yyvsp[-1].cl);
				(yyval.cl).ld=PARS_ALLOC(struct comal_line_data);
				(yyval.cl).ld->lineno=(yyvsp[-2].num);
				(yyval.cl).ld->rem=(yyvsp[0].str);
				(yyval.cl).lineptr=NULL;
			}
#line 2067 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 6: /* comal_line: simple_stat  */
#line 269 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl)=(yyvsp[0].cl);
				(yyval.cl).ld=NULL;
			}
#line 2076 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 7: /* comal_line: optrem  */
#line 274 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=0;
			}
#line 2084 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 9: /* optrem: %empty  */
#line 281 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.str)=NULL;
			}
#line 2092 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 10: /* command: quitSYM  */
#line 288 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=quitSYM;
			}
#line 2100 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 12: /* command: saveSYM optfilename  */
#line 293 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=saveSYM;
				(yyval.cl).lc.str=(yyvsp[0].str);
			}
#line 2109 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 13: /* command: loadSYM optfilename  */
#line 298 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=loadSYM;
				(yyval.cl).lc.str=(yyvsp[0].str);
			}
#line 2118 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 14: /* command: enterSYM stringSYM  */
#line 303 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=enterSYM;
				(yyval.cl).lc.str=(yyvsp[0].str);
			}
#line 2127 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 15: /* command: envSYM optid2  */
#line 308 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=envSYM;
				(yyval.cl).lc.id=(yyvsp[0].id);
			}
#line 2136 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 16: /* command: runSYM  */
#line 313 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=COMMAND(runSYM);
				(yyval.cl).lc.str=NULL;
			}
#line 2145 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 17: /* command: newSYM  */
#line 318 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=newSYM;
			}
#line 2153 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 18: /* command: scanSYM  */
#line 322 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=scanSYM;
			}
#line 2161 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 19: /* command: autoSYM autolines  */
#line 326 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=autoSYM;
				(yyval.cl).lc.twonum=(yyvsp[0].twonum);
			}
#line 2170 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 20: /* command: contSYM  */
#line 331 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=contSYM;
			}
#line 2178 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 21: /* command: delSYM line_range  */
#line 335 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=COMMAND(delSYM);
				(yyval.cl).lc.twonum=(yyvsp[0].twonum);
			}
#line 2187 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 22: /* command: editSYM line_range  */
#line 340 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=editSYM;
				(yyval.cl).lc.twonum=(yyvsp[0].twonum);
			}
#line 2196 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 23: /* command: renumberSYM renumlines  */
#line 345 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=renumberSYM;
				(yyval.cl).lc.twonum=(yyvsp[0].twonum);
			}
#line 2205 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 24: /* list_cmd: listSYM line_range  */
#line 352 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=listSYM;
				(yyval.cl).lc.listrec.str=NULL;
				(yyval.cl).lc.listrec.twonum=(yyvsp[0].twonum);
				(yyval.cl).lc.listrec.id=NULL;
			}
#line 2216 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 25: /* list_cmd: listSYM stringSYM  */
#line 359 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=listSYM;
				(yyval.cl).lc.listrec.str=(yyvsp[0].str);
				(yyval.cl).lc.listrec.twonum.num1=0;
				(yyval.cl).lc.listrec.twonum.num2=INT_MAX;
				(yyval.cl).lc.listrec.id=NULL;
			}
#line 2228 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 26: /* list_cmd: listSYM line_range commaSYM stringSYM  */
#line 367 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=listSYM;
				(yyval.cl).lc.listrec.str=(yyvsp[0].str);
				(yyval.cl).lc.listrec.twonum=(yyvsp[-2].twonum);
				(yyval.cl).lc.listrec.id=NULL;
			}
#line 2239 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 27: /* list_cmd: listSYM id  */
#line 374 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=listSYM;
				(yyval.cl).lc.listrec.str=NULL;
				(yyval.cl).lc.listrec.id=(yyvsp[0].id);
			}
#line 2249 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 28: /* list_cmd: listSYM id commaSYM stringSYM  */
#line 380 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=listSYM;
				(yyval.cl).lc.listrec.str=(yyvsp[0].str);
				(yyval.cl).lc.listrec.id=(yyvsp[-2].id);
			}
#line 2259 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 29: /* line_range: %empty  */
#line 388 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twonum).num1=0;	(yyval.twonum).num2=INT_MAX;
			}
#line 2267 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 30: /* line_range: intnumSYM  */
#line 392 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twonum).num1=(yyvsp[0].num);	(yyval.twonum).num2=(yyvsp[0].num);
			}
#line 2275 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 31: /* line_range: minusSYM intnumSYM  */
#line 396 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twonum).num1=0;	(yyval.twonum).num2=(yyvsp[0].num);
			}
#line 2283 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 32: /* line_range: intnumSYM minusSYM  */
#line 400 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twonum).num1=(yyvsp[-1].num);	(yyval.twonum).num2=INT_MAX;
			}
#line 2291 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 33: /* line_range: intnumSYM minusSYM intnumSYM  */
#line 404 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twonum).num1=(yyvsp[-2].num);	(yyval.twonum).num2=(yyvsp[0].num);
			}
#line 2299 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 34: /* renumlines: intnumSYM  */
#line 410 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twonum).num1=(yyvsp[0].num);	(yyval.twonum).num2=10;
			}
#line 2307 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 35: /* renumlines: intnumSYM commaSYM intnumSYM  */
#line 414 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twonum).num1=(yyvsp[-2].num);	(yyval.twonum).num2=(yyvsp[0].num);
			}
#line 2315 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 36: /* renumlines: commaSYM intnumSYM  */
#line 418 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twonum).num1=10;	(yyval.twonum).num2=(yyvsp[0].num);
			}
#line 2323 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 37: /* renumlines: %empty  */
#line 422 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twonum).num1=10;	(yyval.twonum).num2=10;
			}
#line 2331 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 38: /* autolines: intnumSYM  */
#line 428 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twonum).num1=(yyvsp[0].num);	(yyval.twonum).num2=10;
			}
#line 2339 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 39: /* autolines: intnumSYM commaSYM intnumSYM  */
#line 432 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twonum).num1=(yyvsp[-2].num);	(yyval.twonum).num2=(yyvsp[0].num);
			}
#line 2347 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 40: /* autolines: commaSYM intnumSYM  */
#line 436 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twonum).num1=prog_highest_line()+(yyvsp[0].num);	
				(yyval.twonum).num2=(yyvsp[0].num);
			}
#line 2356 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 41: /* autolines: %empty  */
#line 441 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twonum).num1=prog_highest_line()+10;	
				(yyval.twonum).num2=10;
			}
#line 2365 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 44: /* program_line: %empty  */
#line 450 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=0;
			}
#line 2373 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 86: /* simple_stat: xid  */
#line 499 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=execSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 2382 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 89: /* complex_1word: elseSYM  */
#line 508 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=elseSYM;
			}
#line 2390 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 90: /* complex_1word: endcaseSYM  */
#line 512 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=endcaseSYM;
			}
#line 2398 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 91: /* complex_1word: endfuncSYM optid  */
#line 516 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=endfuncSYM;
			}
#line 2406 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 92: /* complex_1word: endifSYM  */
#line 520 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=endifSYM;
			}
#line 2414 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 93: /* complex_1word: loopSYM  */
#line 524 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=loopSYM;
			}
#line 2422 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 94: /* complex_1word: endloopSYM  */
#line 528 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=endloopSYM;
			}
#line 2430 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 95: /* complex_1word: endprocSYM optid2  */
#line 532 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=endprocSYM;
			}
#line 2438 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 96: /* complex_1word: endwhileSYM  */
#line 536 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=endwhileSYM;
			}
#line 2446 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 97: /* complex_1word: endforSYM optnumlvalue  */
#line 540 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=endforSYM;
			}
#line 2454 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 98: /* complex_1word: otherwiseSYM  */
#line 544 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=otherwiseSYM;
			}
#line 2462 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 99: /* complex_1word: repeatSYM  */
#line 548 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=repeatSYM;
				(yyval.cl).lc.ifwhilerec.exp=NULL;
				(yyval.cl).lc.ifwhilerec.stat=NULL;
			}
#line 2472 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 100: /* complex_1word: trapSYM  */
#line 554 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=trapSYM;
				(yyval.cl).lc.traprec.esc=0;
			}
#line 2481 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 101: /* complex_1word: handlerSYM  */
#line 559 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=handlerSYM;
			}
#line 2489 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 102: /* complex_1word: endtrapSYM  */
#line 563 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=endtrapSYM;
			}
#line 2497 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 103: /* simple_1word: nullSYM  */
#line 569 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=nullSYM;
			}
#line 2505 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 104: /* simple_1word: endSYM  */
#line 573 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=endSYM;
			}
#line 2513 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 105: /* simple_1word: exitSYM  */
#line 577 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=exitSYM;
				(yyval.cl).lc.exp=NULL;
			}
#line 2522 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 106: /* simple_1word: pageSYM  */
#line 582 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=pageSYM;
			}
#line 2530 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 107: /* simple_1word: retrySYM  */
#line 586 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=retrySYM;
			}
#line 2538 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 108: /* case_stat: caseSYM exp optof  */
#line 592 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=caseSYM;
				(yyval.cl).lc.exp=(yyvsp[-1].exp);
			}
#line 2547 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 109: /* close_stat: closeSYM  */
#line 599 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=closeSYM;
				(yyval.cl).lc.exproot=NULL;
			}
#line 2556 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 110: /* close_stat: closeSYM optfileS exp_list  */
#line 604 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=closeSYM;
				(yyval.cl).lc.exproot=PARS_REVERSE(struct exp_list, (yyvsp[0].expptr));
			}
#line 2565 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 111: /* cursor_stat: cursorSYM numexp commaSYM numexp  */
#line 611 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=cursorSYM;
				(yyval.cl).lc.twoexp.exp1=(yyvsp[-2].exp);
				(yyval.cl).lc.twoexp.exp2=(yyvsp[0].exp);
			}
#line 2575 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 112: /* chdir_stat: chdirSYM stringexp  */
#line 619 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=chdirSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 2584 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 113: /* rmdir_stat: rmdirSYM stringexp  */
#line 626 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=rmdirSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 2593 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 114: /* mkdir_stat: mkdirSYM stringexp  */
#line 633 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=mkdirSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 2602 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 115: /* data_stat: dataSYM exp_list  */
#line 640 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=dataSYM;
				(yyval.cl).lc.exproot=PARS_REVERSE(struct exp_list, (yyvsp[0].expptr));
			}
#line 2611 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 116: /* del_stat: delSYM stringexp  */
#line 647 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=delSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 2620 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 117: /* dir_stat: dirSYM opt_stringexp  */
#line 654 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=dirSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 2629 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 118: /* unit_stat: unitSYM stringexp  */
#line 661 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=unitSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 2638 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 119: /* local_stat: localSYM local_list  */
#line 669 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=localSYM;
				(yyval.cl).lc.dimroot=PARS_REVERSE(struct dim_list, (yyvsp[0].dimptr));
			}
#line 2647 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 120: /* local_list: local_list commaSYM local_item  */
#line 675 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=(yyvsp[0].dimptr);
				(yyval.dimptr)->next=(yyvsp[-2].dimptr);
			}
#line 2656 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 121: /* local_list: local_item  */
#line 680 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=(yyvsp[0].dimptr);
				(yyval.dimptr)->next=NULL;
			}
#line 2665 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 122: /* local_item: numid opt_dim_ensions  */
#line 687 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[-1].id),NULL,(yyvsp[0].dimensionptr));
			}
#line 2673 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 123: /* local_item: stringidSYM  */
#line 691 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[0].id),NULL,NULL);
			}
#line 2681 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 124: /* local_item: stringidSYM ofSYM numexp  */
#line 695 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[-2].id),(yyvsp[0].exp),NULL);
			}
#line 2689 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 125: /* local_item: stringidSYM dim_ensions of numexp  */
#line 699 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[-3].id),(yyvsp[0].exp),(yyvsp[-2].dimensionptr));
			}
#line 2697 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 126: /* local_item: stringidSYM dim_ensions  */
#line 703 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[-1].id),NULL,(yyvsp[0].dimensionptr));
			}
#line 2705 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 127: /* dim_stat: dimSYM dim_list  */
#line 710 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=dimSYM;
				(yyval.cl).lc.dimroot=PARS_REVERSE(struct dim_list, (yyvsp[0].dimptr));
			}
#line 2714 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 128: /* dim_list: dim_list commaSYM dim_item  */
#line 717 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=(yyvsp[0].dimptr);
				(yyval.dimptr)->next=(yyvsp[-2].dimptr);
			}
#line 2723 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 129: /* dim_list: dim_item  */
#line 722 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=(yyvsp[0].dimptr);
				(yyval.dimptr)->next=NULL;
			}
#line 2732 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 130: /* dim_item: numid dim_ensions  */
#line 729 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[-1].id),NULL,(yyvsp[0].dimensionptr));
			}
#line 2740 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 131: /* dim_item: stringidSYM ofSYM numexp  */
#line 733 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[-2].id),(yyvsp[0].exp),NULL);
			}
#line 2748 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 132: /* dim_item: stringidSYM dim_ensions of numexp  */
#line 737 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[-3].id),(yyvsp[0].exp),(yyvsp[-2].dimensionptr));
			}
#line 2756 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 133: /* dim_item: stringidSYM dim_ensions  */
#line 741 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[-1].id),NULL,(yyvsp[0].dimensionptr));
			}
#line 2764 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 137: /* opt_dim_ensions: %empty  */
#line 752 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimensionptr)=NULL;
			}
#line 2772 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 138: /* dim_ensions: lparenSYM dim_ension_list rparenSYM  */
#line 758 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimensionptr)=(yyvsp[-1].dimensionptr);
			}
#line 2780 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 139: /* dim_ension_list: dim_ension_list commaSYM dim_ension  */
#line 764 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimensionptr)=(yyvsp[0].dimensionptr);
				(yyval.dimensionptr)->next=(yyvsp[-2].dimensionptr);
			}
#line 2789 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 140: /* dim_ension_list: dim_ension  */
#line 769 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimensionptr)=(yyvsp[0].dimensionptr);
				(yyval.dimensionptr)->next=NULL;
			}
#line 2798 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 141: /* dim_ension: numexp  */
#line 776 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimensionptr)=PARS_ALLOC(struct dim_ension);
				(yyval.dimensionptr)->bottom=NULL;
				(yyval.dimensionptr)->top=(yyvsp[0].exp);
			}
#line 2808 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 142: /* dim_ension: numexp colonSYM numexp  */
#line 782 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimensionptr)=PARS_ALLOC(struct dim_ension);
				(yyval.dimensionptr)->bottom=(yyvsp[-2].exp);
				(yyval.dimensionptr)->top=(yyvsp[0].exp);
			}
#line 2818 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 143: /* dim_ension: numexp becminusSYM numexp  */
#line 788 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimensionptr)=PARS_ALLOC(struct dim_ension);
				(yyval.dimensionptr)->bottom=(yyvsp[-2].exp);
				(yyval.dimensionptr)->top=pars_exp_unary(minusSYM,(yyvsp[0].exp));
			}
#line 2828 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 144: /* elif_stat: elifSYM numexp optthen  */
#line 796 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=elifSYM;
				(yyval.cl).lc.exp=(yyvsp[-1].exp);
			}
#line 2837 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 145: /* exit_stat: exitSYM ifwhen numexp  */
#line 803 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=exitSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 2846 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 148: /* exec_stat: execSYM xid  */
#line 814 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=execSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 2855 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 149: /* for_stat: forSYM numlvalue assign1 numexp todownto numexp optstep optdo optsimple_stat  */
#line 821 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=forSYM;
				(yyval.cl).lc.forrec.lval=(yyvsp[-7].exp);
				(yyval.cl).lc.forrec.from=(yyvsp[-5].exp);
				(yyval.cl).lc.forrec.mode=(yyvsp[-4].inum);
				(yyval.cl).lc.forrec.to=(yyvsp[-3].exp);
				(yyval.cl).lc.forrec.step=(yyvsp[-2].exp);
				(yyval.cl).lc.forrec.stat=(yyvsp[0].pcl);
			}
#line 2869 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 150: /* todownto: toSYM  */
#line 833 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=toSYM;
			}
#line 2877 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 151: /* todownto: downtoSYM  */
#line 837 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=downtoSYM;
			}
#line 2885 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 152: /* optstep: stepSYM numexp  */
#line 843 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=(yyvsp[0].exp);
			}
#line 2893 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 153: /* optstep: %empty  */
#line 847 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=NULL;
			}
#line 2901 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 154: /* func_stat: funcSYM id procfunc_head optclosed opt_external  */
#line 853 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=funcSYM;
				(yyval.cl).lc.pfrec.id=(yyvsp[-3].id);
				(yyval.cl).lc.pfrec.parmroot=PARS_REVERSE(struct parm_list, (yyvsp[-2].parmptr));
				(yyval.cl).lc.pfrec.closed=(yyvsp[-1].inum);
				(yyval.cl).lc.pfrec.external=(yyvsp[0].extptr);
			}
#line 2913 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 155: /* if_stat: ifSYM numexp optthen optsimple_stat  */
#line 863 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=ifSYM;
				(yyval.cl).lc.ifwhilerec.exp=(yyvsp[-2].exp);
				(yyval.cl).lc.ifwhilerec.stat=(yyvsp[0].pcl);
			}
#line 2923 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 156: /* import_stat: importSYM id colonSYM import_list  */
#line 871 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=importSYM;
				(yyval.cl).lc.importrec.id=(yyvsp[-2].id);
				(yyval.cl).lc.importrec.importroot=PARS_REVERSE(struct import_list, (yyvsp[0].importptr));
			}
#line 2933 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 157: /* import_stat: importSYM import_list  */
#line 877 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=importSYM;
				(yyval.cl).lc.importrec.id=NULL;
				(yyval.cl).lc.importrec.importroot=PARS_REVERSE(struct import_list, (yyvsp[0].importptr));
			}
#line 2943 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 158: /* import_list: import_list commaSYM oneparm  */
#line 885 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.importptr)=PARS_ALLOC(struct import_list);
				(yyval.importptr)->id=(yyvsp[0].oneparm).id;
				(yyval.importptr)->array=(yyvsp[0].oneparm).array;
				(yyval.importptr)->next=(yyvsp[-2].importptr);				
			}
#line 2954 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 159: /* import_list: oneparm  */
#line 892 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.importptr)=PARS_ALLOC(struct import_list);
				(yyval.importptr)->id=(yyvsp[0].oneparm).id;
				(yyval.importptr)->array=(yyvsp[0].oneparm).array;
				(yyval.importptr)->next=NULL;
			}
#line 2965 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 160: /* input_stat: inputSYM input_modifier lval_list  */
#line 901 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=inputSYM;
				(yyval.cl).lc.inputrec.modifier=(yyvsp[-1].imod);
				(yyval.cl).lc.inputrec.lvalroot=PARS_REVERSE(struct exp_list, (yyvsp[0].expptr));
			}
#line 2975 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 161: /* input_modifier: file_designator  */
#line 909 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.imod)=PARS_ALLOC(struct input_modifier);
				(yyval.imod)->type=fileSYM;
				(yyval.imod)->data.twoexp=(yyvsp[0].twoexp);
			}
#line 2985 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 162: /* input_modifier: stringSYM colonSYM  */
#line 915 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.imod)=PARS_ALLOC(struct input_modifier);
				(yyval.imod)->type=stringSYM;
				(yyval.imod)->data.str=(yyvsp[-1].str);
			}
#line 2995 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 163: /* input_modifier: %empty  */
#line 921 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.imod)=NULL;
			}
#line 3003 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 164: /* open_stat: openSYM fileSYM numexp commaSYM stringexp commaSYM open_type  */
#line 927 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=openSYM;
				(yyval.cl).lc.openrec=(yyvsp[0].openrec);
				(yyval.cl).lc.openrec.filenum=(yyvsp[-4].exp);
				(yyval.cl).lc.openrec.filename=(yyvsp[-2].exp);
			}
#line 3014 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 165: /* open_type: readSYM  */
#line 936 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.openrec).type=readSYM;
			}
#line 3022 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 166: /* open_type: writeSYM  */
#line 940 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.openrec).type=writeSYM;
			}
#line 3030 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 167: /* open_type: appendSYM  */
#line 944 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.openrec).type=appendSYM;
			}
#line 3038 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 168: /* open_type: randomSYM numexp optread_only  */
#line 948 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.openrec).type=randomSYM;
				(yyval.openrec).reclen=(yyvsp[-1].exp);
				(yyval.openrec).read_only=(yyvsp[0].inum);
			}
#line 3048 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 169: /* os_stat: osSYM stringexp  */
#line 956 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=osSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 3057 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 170: /* print_stat: printi  */
#line 963 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=printSYM;
				(yyval.cl).lc.printrec.modifier=NULL;
				(yyval.cl).lc.printrec.printroot=NULL;
				(yyval.cl).lc.printrec.pr_sep=0;
			}
#line 3068 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 171: /* print_stat: printi print_list optpr_sep  */
#line 970 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=printSYM;
				(yyval.cl).lc.printrec.modifier=NULL;
				(yyval.cl).lc.printrec.printroot=PARS_REVERSE(struct print_list, (yyvsp[-1].printptr));
				(yyval.cl).lc.printrec.pr_sep=(yyvsp[0].inum);
			}
#line 3079 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 172: /* print_stat: printi usingSYM stringexp colonSYM prnum_list optpr_sep  */
#line 977 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=printSYM;
				(yyval.cl).lc.printrec.modifier=PARS_ALLOC(struct print_modifier);
				(yyval.cl).lc.printrec.modifier->type=usingSYM;
				(yyval.cl).lc.printrec.modifier->data.str=(yyvsp[-3].exp);
				(yyval.cl).lc.printrec.printroot=PARS_REVERSE(struct print_list, (yyvsp[-1].printptr));
				(yyval.cl).lc.printrec.pr_sep=(yyvsp[0].inum);
			}
#line 3092 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 173: /* print_stat: printi file_designator print_list  */
#line 986 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=printSYM;
				(yyval.cl).lc.printrec.modifier=PARS_ALLOC(struct print_modifier);
				(yyval.cl).lc.printrec.modifier->type=fileSYM;
				(yyval.cl).lc.printrec.modifier->data.twoexp=(yyvsp[-1].twoexp);
				(yyval.cl).lc.printrec.printroot=PARS_REVERSE(struct print_list, (yyvsp[0].printptr));
				(yyval.cl).lc.printrec.pr_sep=0;
			}
#line 3105 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 176: /* prnum_list: prnum_list pr_sep numexp  */
#line 1001 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.printptr)=pars_printlist_item((yyvsp[-1].inum),(yyvsp[0].exp),(yyvsp[-2].printptr));
			}
#line 3113 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 177: /* prnum_list: numexp  */
#line 1005 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.printptr)=pars_printlist_item(0,(yyvsp[0].exp),NULL);
			}
#line 3121 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 178: /* print_list: print_list pr_sep exp  */
#line 1011 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.printptr)=pars_printlist_item((yyvsp[-1].inum),(yyvsp[0].exp),(yyvsp[-2].printptr));
			}
#line 3129 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 179: /* print_list: exp  */
#line 1015 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.printptr)=pars_printlist_item(0,(yyvsp[0].exp),NULL);
			}
#line 3137 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 180: /* pr_sep: commaSYM  */
#line 1021 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=commaSYM;
			}
#line 3145 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 181: /* pr_sep: semicolonSYM  */
#line 1025 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=semicolonSYM;
			}
#line 3153 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 183: /* optpr_sep: %empty  */
#line 1032 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=0;
			}
#line 3161 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 184: /* proc_stat: procSYM idSYM procfunc_head optclosed opt_external  */
#line 1038 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=procSYM;
				(yyval.cl).lc.pfrec.id=(yyvsp[-3].id);
				(yyval.cl).lc.pfrec.parmroot=PARS_REVERSE(struct parm_list, (yyvsp[-2].parmptr));
				(yyval.cl).lc.pfrec.closed=(yyvsp[-1].inum);
				(yyval.cl).lc.pfrec.external=(yyvsp[0].extptr);
			}
#line 3173 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 185: /* read_stat: readSYM optfile lval_list  */
#line 1048 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=readSYM;
				(yyval.cl).lc.readrec.modifier=(yyvsp[-1].twoexpp);
				(yyval.cl).lc.readrec.lvalroot=PARS_REVERSE(struct exp_list, (yyvsp[0].expptr));
			}
#line 3183 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 186: /* restore_stat: restoreSYM optid2  */
#line 1056 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=restoreSYM;
				(yyval.cl).lc.id=(yyvsp[0].id);
			}
#line 3192 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 187: /* return_stat: returnSYM optexp  */
#line 1063 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=returnSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 3201 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 188: /* run_stat: runSYM stringexp  */
#line 1070 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=runSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 3210 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 189: /* select_out_stat: select_outputSYM stringexp  */
#line 1077 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=select_outputSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 3219 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 190: /* select_in_stat: select_inputSYM stringexp  */
#line 1085 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=select_inputSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 3228 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 191: /* stop_stat: stopSYM optexp  */
#line 1092 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=stopSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 3237 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 192: /* sys_stat: sysSYM exp_list  */
#line 1099 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=sysSYM;
				(yyval.cl).lc.exproot=PARS_REVERSE(struct exp_list, (yyvsp[0].expptr));
			}
#line 3246 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 193: /* until_stat: untilSYM numexp  */
#line 1106 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=untilSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 3255 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 194: /* trace_stat: traceSYM numexp  */
#line 1113 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				char *cmd=exp_cmd((yyvsp[0].exp));
				
				if (strcmp(cmd,"on")!=0 && strcmp(cmd,"off")!=0)
					pars_error("TRACE \"on\" or \"off\"");
				
				(yyval.cl).cmd=traceSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 3269 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 195: /* trap_stat: trapSYM escSYM plusorminus  */
#line 1125 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=trapSYM;
				(yyval.cl).lc.traprec.esc=(yyvsp[0].inum);
			}
#line 3278 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 196: /* plusorminus: plusSYM  */
#line 1132 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=plusSYM;
			}
#line 3286 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 197: /* plusorminus: minusSYM  */
#line 1136 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=minusSYM;
			}
#line 3294 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 198: /* when_stat: whenSYM when_list  */
#line 1142 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=whenSYM;
				(yyval.cl).lc.whenroot=PARS_REVERSE(struct when_list, (yyvsp[0].whenptr));
			}
#line 3303 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 201: /* when_numlist: when_numlist commaSYM when_numitem  */
#line 1153 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.whenptr)=(yyvsp[0].whenptr);
				(yyval.whenptr)->next=(yyvsp[-2].whenptr);
			}
#line 3312 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 203: /* when_numitem: relop numexp  */
#line 1161 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.whenptr)=pars_whenlist_item((yyvsp[-1].inum),(yyvsp[0].exp),NULL);
			}
#line 3320 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 204: /* when_numitem: numexp  */
#line 1165 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.whenptr)=pars_whenlist_item(eqlSYM,(yyvsp[0].exp),NULL);
			}
#line 3328 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 205: /* when_strlist: when_strlist commaSYM when_stritem  */
#line 1171 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.whenptr)=(yyvsp[0].whenptr);
				(yyval.whenptr)->next=(yyvsp[-2].whenptr);
			}
#line 3337 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 207: /* when_stritem: relop stringexp  */
#line 1179 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.whenptr)=pars_whenlist_item((yyvsp[-1].inum),(yyvsp[0].exp),NULL);
			}
#line 3345 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 208: /* when_stritem: stringexp  */
#line 1183 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.whenptr)=pars_whenlist_item(eqlSYM,(yyvsp[0].exp),NULL);
			}
#line 3353 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 209: /* when_stritem: inSYM stringexp  */
#line 1187 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.whenptr)=pars_whenlist_item(inSYM,(yyvsp[0].exp),NULL);
			}
#line 3361 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 210: /* relop: gtrSYM  */
#line 1193 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=gtrSYM;
			}
#line 3369 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 211: /* relop: lssSYM  */
#line 1197 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=lssSYM;
			}
#line 3377 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 212: /* relop: eqlSYM  */
#line 1201 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=eqlSYM;
			}
#line 3385 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 213: /* relop: neqSYM  */
#line 1205 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=neqSYM;
			}
#line 3393 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 214: /* relop: geqSYM  */
#line 1209 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=geqSYM;
			}
#line 3401 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 215: /* relop: leqSYM  */
#line 1213 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=leqSYM;
			}
#line 3409 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 216: /* while_stat: whileSYM numexp optdo optsimple_stat  */
#line 1219 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=whileSYM;
				(yyval.cl).lc.ifwhilerec.exp=(yyvsp[-2].exp);
				(yyval.cl).lc.ifwhilerec.stat=(yyvsp[0].pcl);
			}
#line 3419 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 217: /* repeat_stat: repeatSYM simple_stat untilSYM numexp  */
#line 1227 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=repeatSYM;
				(yyval.cl).lc.ifwhilerec.exp=(yyvsp[0].exp);
				(yyval.cl).lc.ifwhilerec.stat=stat_dup(&(yyvsp[-2].cl));
			}
#line 3429 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 218: /* write_stat: writeSYM file_designator exp_list  */
#line 1235 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=writeSYM;
				(yyval.cl).lc.writerec.twoexp=(yyvsp[-1].twoexp);
				(yyval.cl).lc.writerec.exproot=PARS_REVERSE(struct exp_list, (yyvsp[0].expptr));
			}
#line 3439 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 219: /* assign_stat: assign_list  */
#line 1243 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=becomesSYM;
				(yyval.cl).lc.assignroot=PARS_REVERSE(struct assign_list, (yyvsp[0].assignptr));
			}
#line 3448 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 220: /* assign_list: assign_list semicolonSYM assign_item  */
#line 1250 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.assignptr)=(yyvsp[0].assignptr);
				(yyval.assignptr)->next=(yyvsp[-2].assignptr);
			}
#line 3457 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 221: /* assign_list: assign_item  */
#line 1255 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.assignptr)->next=NULL;
			}
#line 3465 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 222: /* assign_item: numlvalue nassign numexp  */
#line 1261 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.assignptr)=pars_assign_item((yyvsp[-1].inum),(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3473 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 223: /* assign_item: strlvalue sassign stringexp  */
#line 1265 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.assignptr)=pars_assign_item((yyvsp[-1].inum),(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3481 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 227: /* sassign: becplusSYM  */
#line 1276 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=becplusSYM;
			}
#line 3489 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 228: /* assign1: eqlSYM  */
#line 1282 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=becomesSYM;
			}
#line 3497 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 229: /* assign1: becomesSYM  */
#line 1286 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=becomesSYM;
			}
#line 3505 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 230: /* assign2: becplusSYM  */
#line 1292 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=becplusSYM;
			}
#line 3513 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 231: /* assign2: becminusSYM  */
#line 1296 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=becminusSYM;
			}
#line 3521 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 232: /* label_stat: idSYM colonSYM  */
#line 1302 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=idSYM;
				(yyval.cl).lc.id=(yyvsp[-1].id);
			}
#line 3530 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 233: /* xid: idSYM  */
#line 1309 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_id(idSYM,(yyvsp[0].id),NULL);
			}
#line 3538 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 234: /* xid: idSYM lparenSYM exp_list rparenSYM  */
#line 1313 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_id(idSYM,(yyvsp[-3].id),(yyvsp[-1].expptr));
			}
#line 3546 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 235: /* xid: idSYM lparenSYM opt_commalist rparenSYM  */
#line 1317 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_array(idSYM,(yyvsp[-3].id),T_ARRAY);
			}
#line 3554 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 238: /* numexp: numexp2  */
#line 1327 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_num((yyvsp[0].exp));
			}
#line 3562 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 239: /* numexp2: numexp2 eqlSYM numexp2  */
#line 1333 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(eqlSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3570 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 240: /* numexp2: numexp2 neqSYM numexp2  */
#line 1337 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(neqSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3578 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 241: /* numexp2: numexp2 lssSYM numexp2  */
#line 1341 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(lssSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3586 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 242: /* numexp2: numexp2 gtrSYM numexp2  */
#line 1345 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(gtrSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3594 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 243: /* numexp2: numexp2 leqSYM numexp2  */
#line 1349 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(leqSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3602 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 244: /* numexp2: numexp2 geqSYM numexp2  */
#line 1353 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(geqSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3610 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 245: /* numexp2: numexp2 andSYM numexp2  */
#line 1357 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(andSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3618 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 246: /* numexp2: numexp2 andthenSYM numexp2  */
#line 1361 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(andthenSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3626 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 247: /* numexp2: numexp2 orSYM numexp2  */
#line 1365 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(orSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3634 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 248: /* numexp2: numexp2 orthenSYM numexp2  */
#line 1369 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(orthenSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3642 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 249: /* numexp2: numexp2 eorSYM numexp2  */
#line 1373 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(eorSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3650 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 250: /* numexp2: numexp2 plusSYM numexp2  */
#line 1377 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(plusSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3658 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 251: /* numexp2: numexp2 minusSYM numexp2  */
#line 1381 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(minusSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3666 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 252: /* numexp2: numexp2 timesSYM numexp2  */
#line 1385 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(timesSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3674 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 253: /* numexp2: numexp2 divideSYM numexp2  */
#line 1389 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(divideSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3682 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 254: /* numexp2: numexp2 powerSYM numexp2  */
#line 1393 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(powerSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3690 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 255: /* numexp2: numexp2 divSYM numexp2  */
#line 1397 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(divSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3698 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 256: /* numexp2: numexp2 modSYM numexp2  */
#line 1401 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(modSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3706 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 257: /* numexp2: stringexp2 eqlSYM stringexp2  */
#line 1405 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(eqlSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3714 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 258: /* numexp2: stringexp2 neqSYM stringexp2  */
#line 1409 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(neqSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3722 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 259: /* numexp2: stringexp2 lssSYM stringexp2  */
#line 1413 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(lssSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3730 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 260: /* numexp2: stringexp2 gtrSYM stringexp2  */
#line 1417 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(gtrSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3738 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 261: /* numexp2: stringexp2 leqSYM stringexp2  */
#line 1421 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(leqSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3746 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 262: /* numexp2: stringexp2 geqSYM stringexp2  */
#line 1425 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(geqSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3754 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 263: /* numexp2: stringexp2 inSYM stringexp2  */
#line 1429 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(inSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3762 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 264: /* numexp2: minusSYM numexp2  */
#line 1433 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary(minusSYM,(yyvsp[0].exp));
			}
#line 3770 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 265: /* numexp2: plusSYM numexp2  */
#line 1437 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary(plusSYM,(yyvsp[0].exp));
			}
#line 3778 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 266: /* numexp2: intnumSYM  */
#line 1441 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_int((yyvsp[0].num));
			}
#line 3786 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 267: /* numexp2: floatnumSYM  */
#line 1445 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_float(&(yyvsp[0].dubbel));
			}
#line 3794 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 269: /* numexp2: tsrnSYM lparenSYM stringexp2 rparenSYM  */
#line 1450 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary((yyvsp[-3].inum),(yyvsp[-1].exp));
			}
#line 3802 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 270: /* numexp2: tnrnSYM lparenSYM numexp2 rparenSYM  */
#line 1454 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary((yyvsp[-3].inum),(yyvsp[-1].exp));
			}
#line 3810 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 271: /* numexp2: rndSYM  */
#line 1458 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(_RND,NULL,NULL);
			}
#line 3818 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 272: /* numexp2: rndSYM lparenSYM numexp2 rparenSYM  */
#line 1462 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(_RND,NULL,(yyvsp[-1].exp));
			}
#line 3826 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 273: /* numexp2: rndSYM lparenSYM numexp2 commaSYM numexp2 rparenSYM  */
#line 1466 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(_RND,(yyvsp[-3].exp),(yyvsp[-1].exp));
			}
#line 3834 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 274: /* numexp2: rnSYM  */
#line 1470 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_const((yyvsp[0].inum));
			}
#line 3842 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 275: /* numexp2: sysSYM lparenSYM exp_list rparenSYM  */
#line 1474 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_sys(sysSYM,T_SYS,(yyvsp[-1].expptr));
			}
#line 3850 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 276: /* numexp2: lparenSYM numexp2 rparenSYM  */
#line 1478 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary(lparenSYM,(yyvsp[-1].exp));
			}
#line 3858 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 277: /* stringexp: stringexp2  */
#line 1484 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_str((yyvsp[0].exp));
			}
#line 3866 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 278: /* stringexp2: stringexp2 plusSYM string_factor  */
#line 1490 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(plusSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3874 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 280: /* stringexp2: stringexp2 timesSYM numexp2  */
#line 1495 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(timesSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3882 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 282: /* opt_stringexp: %empty  */
#line 1502 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=NULL;
			}
#line 3890 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 284: /* string_factor: string_factor substr_spec  */
#line 1509 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_substr((yyvsp[-1].exp),&(yyvsp[0].twoexp));
			}
#line 3898 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 285: /* string_factor: tnrsSYM lparenSYM numexp2 rparenSYM  */
#line 1513 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary((yyvsp[-3].inum),(yyvsp[-1].exp));
			}
#line 3906 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 286: /* string_factor: tsrsSYM lparenSYM stringexp2 rparenSYM  */
#line 1517 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary((yyvsp[-3].inum),(yyvsp[-1].exp));
			}
#line 3914 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 287: /* string_factor: rsSYM  */
#line 1521 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_const((yyvsp[0].inum));
			}
#line 3922 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 288: /* string_factor: tonrsSYM opt_arg  */
#line 1525 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary((yyvsp[-1].inum),(yyvsp[0].exp));
			}
#line 3930 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 289: /* string_factor: stringSYM  */
#line 1529 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_string((yyvsp[0].str));
			}
#line 3938 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 290: /* string_factor: syssSYM lparenSYM exp_list rparenSYM  */
#line 1533 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_sys(syssSYM,T_SYSS,(yyvsp[-1].expptr));
			}
#line 3946 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 291: /* string_factor: tsrsnSYM lparenSYM exp_list rparenSYM  */
#line 1537 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
			(yyval.exp)=pars_exp_sys((yyvsp[-3].inum),T_SYSS,(yyvsp[-1].expptr));
			}
#line 3954 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 292: /* string_factor: lparenSYM stringexp2 rparenSYM  */
#line 1541 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary(lparenSYM,(yyvsp[-1].exp));
			}
#line 3962 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 293: /* opt_arg: lparenSYM numexp2 rparenSYM  */
#line 1547 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=(yyvsp[-1].exp);
			}
#line 3970 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 294: /* opt_arg: %empty  */
#line 1551 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=NULL;
			}
#line 3978 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 295: /* substr_spec: lparenSYM substr_spec2 rparenSYM  */
#line 1557 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp)=(yyvsp[-1].twoexp);
			}
#line 3986 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 296: /* substr_spec2: numexp colonSYM numexp  */
#line 1563 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp).exp1=(yyvsp[-2].exp);
				(yyval.twoexp).exp2=(yyvsp[0].exp);
			}
#line 3995 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 297: /* substr_spec2: colonSYM numexp  */
#line 1568 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp).exp1=NULL;
				(yyval.twoexp).exp2=(yyvsp[0].exp);
			}
#line 4004 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 298: /* substr_spec2: numexp colonSYM  */
#line 1573 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp).exp1=(yyvsp[-1].exp);
				(yyval.twoexp).exp2=NULL;
			}
#line 4013 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 299: /* substr_spec2: colonSYM numexp colonSYM  */
#line 1578 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp).exp1=(yyvsp[-1].exp);
				(yyval.twoexp).exp2=(yyvsp[-1].exp);
			}
#line 4022 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 301: /* optnumlvalue: %empty  */
#line 1586 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=NULL;
			}
#line 4030 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 303: /* optexp: %empty  */
#line 1593 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=NULL;
			}
#line 4038 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 305: /* optid: %empty  */
#line 1600 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.id)=NULL;
			}
#line 4046 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 307: /* optid2: %empty  */
#line 1607 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.id)=NULL;
			}
#line 4054 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 308: /* optfile: file_designator  */
#line 1613 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexpp)=PARS_ALLOC(struct two_exp);
				
				*((yyval.twoexpp))=(yyvsp[0].twoexp);
			}
#line 4064 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 309: /* optfile: %empty  */
#line 1619 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {	
				(yyval.twoexpp)=NULL;
			}
#line 4072 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 312: /* lval_list: lval_list commaSYM lvalue  */
#line 1629 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.expptr)=pars_explist_item((yyvsp[0].exp),(yyvsp[-2].expptr));
			}
#line 4080 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 313: /* lval_list: lvalue  */
#line 1633 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.expptr)=pars_explist_item((yyvsp[0].exp),NULL);
			}
#line 4088 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 316: /* numlvalue: numlvalue2  */
#line 1643 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				if (!exp_list_of_nums((yyvsp[0].exp)->e.expid.exproot))
					pars_error("Indices of numeric lvalue \"%s\" must be numerics",(yyvsp[0].exp)->e.expid.id->name);
			}
#line 4097 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 318: /* numlvalue2: intidSYM  */
#line 1651 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_id(intidSYM,(yyvsp[0].id),NULL);
			}
#line 4105 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 319: /* numlvalue2: intidSYM lparenSYM exp_list rparenSYM  */
#line 1655 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_id(intidSYM,(yyvsp[-3].id),(yyvsp[-1].expptr));
			}
#line 4113 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 320: /* numlvalue2: intidSYM lparenSYM opt_commalist rparenSYM  */
#line 1659 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_array(intidSYM,(yyvsp[-3].id),T_ARRAY);
			}
#line 4121 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 321: /* strlvalue: strlvalue2  */
#line 1665 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				if (!exp_list_of_nums((yyvsp[0].exp)->e.expsid.exproot))
					pars_error("Indices of string lvalue \"%s\" must be numerics",(yyvsp[0].exp)->e.expsid.id->name);
			}
#line 4130 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 322: /* strlvalue2: stringidSYM  */
#line 1672 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_sid((yyvsp[0].id),NULL,NULL);
			}
#line 4138 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 323: /* strlvalue2: stringidSYM lparenSYM exp_list rparenSYM  */
#line 1676 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_sid((yyvsp[-3].id),(yyvsp[-1].expptr),NULL);
			}
#line 4146 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 324: /* strlvalue2: stringidSYM substr_spec  */
#line 1680 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_sid((yyvsp[-1].id),NULL,&(yyvsp[0].twoexp));
			}
#line 4154 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 325: /* strlvalue2: stringidSYM lparenSYM exp_list rparenSYM substr_spec  */
#line 1684 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_sid((yyvsp[-4].id),(yyvsp[-2].expptr),&(yyvsp[0].twoexp));
			}
#line 4162 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 326: /* strlvalue2: stringidSYM lparenSYM opt_commalist rparenSYM  */
#line 1688 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_array(intidSYM,(yyvsp[-3].id),T_SARRAY);
			}
#line 4170 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 327: /* file_designator: fileSYM numexp colonSYM  */
#line 1694 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp).exp1=(yyvsp[-1].exp);
				(yyval.twoexp).exp2=NULL;
			}
#line 4179 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 328: /* file_designator: fileSYM numexp commaSYM numexp colonSYM  */
#line 1699 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp).exp1=(yyvsp[-3].exp);
				(yyval.twoexp).exp2=(yyvsp[-1].exp);
			}
#line 4188 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 329: /* opt_external: externalSYM stringexp  */
#line 1706 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.extptr)=PARS_ALLOC(struct ext_rec);
				
				(yyval.extptr)->dynamic=0;
				(yyval.extptr)->filename=(yyvsp[0].exp);
				(yyval.extptr)->seg=NULL;
			}
#line 4200 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 330: /* opt_external: dynamicSYM externalSYM stringexp  */
#line 1714 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.extptr)=PARS_ALLOC(struct ext_rec);
				
				(yyval.extptr)->dynamic=dynamicSYM;
				(yyval.extptr)->filename=(yyvsp[0].exp);
				(yyval.extptr)->seg=NULL;
			}
#line 4212 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 331: /* opt_external: staticSYM externalSYM stringexp  */
#line 1722 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.extptr)=PARS_ALLOC(struct ext_rec);
				
				(yyval.extptr)->dynamic=staticSYM;
				(yyval.extptr)->filename=(yyvsp[0].exp);
				(yyval.extptr)->seg=NULL;
			}
#line 4224 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 332: /* opt_external: %empty  */
#line 1730 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.extptr)=NULL;
			}
#line 4232 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 333: /* procfunc_head: lparenSYM parmlist rparenSYM  */
#line 1736 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=(yyvsp[-1].parmptr);
			}
#line 4240 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 334: /* procfunc_head: %empty  */
#line 1740 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=NULL;
			}
#line 4248 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 335: /* parmlist: parmlist commaSYM parmitem  */
#line 1746 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=(yyvsp[0].parmptr);
				(yyval.parmptr)->next=(yyvsp[-2].parmptr);
			}
#line 4257 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 336: /* parmlist: parmitem  */
#line 1751 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=(yyvsp[0].parmptr);
				(yyval.parmptr)->next=NULL;
			}
#line 4266 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 337: /* parmitem: oneparm  */
#line 1758 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=PARS_ALLOC(struct parm_list);
				(yyval.parmptr)->id=(yyvsp[0].oneparm).id;
				(yyval.parmptr)->array=(yyvsp[0].oneparm).array;
				(yyval.parmptr)->ref=0;
			}
#line 4277 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 338: /* parmitem: refSYM oneparm  */
#line 1765 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=PARS_ALLOC(struct parm_list);
				(yyval.parmptr)->id=(yyvsp[0].oneparm).id;
				(yyval.parmptr)->array=(yyvsp[0].oneparm).array;
				(yyval.parmptr)->ref=refSYM;
			}
#line 4288 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 339: /* parmitem: nameSYM id  */
#line 1772 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=PARS_ALLOC(struct parm_list);
				(yyval.parmptr)->id=(yyvsp[0].id);
				(yyval.parmptr)->array=0;
				(yyval.parmptr)->ref=nameSYM;
			}
#line 4299 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 340: /* parmitem: procSYM idSYM  */
#line 1779 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=PARS_ALLOC(struct parm_list);
				(yyval.parmptr)->id=(yyvsp[0].id);
				(yyval.parmptr)->array=0;
				(yyval.parmptr)->ref=procSYM;
			}
#line 4310 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 341: /* parmitem: funcSYM id  */
#line 1786 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=PARS_ALLOC(struct parm_list);
				(yyval.parmptr)->id=(yyvsp[0].id);
				(yyval.parmptr)->array=0;
				(yyval.parmptr)->ref=funcSYM;
			}
#line 4321 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 342: /* oneparm: id  */
#line 1795 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.oneparm).id=(yyvsp[0].id);
				(yyval.oneparm).array=0;
			}
#line 4330 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 343: /* oneparm: id lparenSYM opt_commalist rparenSYM  */
#line 1800 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.oneparm).id=(yyvsp[-3].id);
				(yyval.oneparm).array=1;
			}
#line 4339 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 350: /* exp_list: exp_list commaSYM exp  */
#line 1819 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.expptr)=pars_explist_item((yyvsp[0].exp),(yyvsp[-2].expptr));
				}
#line 4347 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 351: /* exp_list: exp  */
#line 1823 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.expptr)=pars_explist_item((yyvsp[0].exp),NULL);
			}
#line 4355 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 352: /* optsimple_stat: simple_stat  */
#line 1829 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				if ((yyvsp[0].cl).cmd<0)
					(yyval.pcl)=NULL;
				else
				{
					(yyval.pcl)=stat_dup(&(yyvsp[0].cl));
					(yyval.pcl)->ld=NULL;
				}
			}
#line 4369 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 353: /* optsimple_stat: %empty  */
#line 1839 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl)=NULL;
			}
#line 4377 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 355: /* optfilename: %empty  */
#line 1846 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.str)=NULL;
			}
#line 4385 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 362: /* optread_only: read_onlySYM  */
#line 1864 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=read_onlySYM;
			}
#line 4393 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 363: /* optread_only: %empty  */
#line 1868 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=0;
			}
#line 4401 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 364: /* optclosed: closedSYM  */
#line 1874 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=closedSYM;
			}
#line 4409 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 365: /* optclosed: %empty  */
#line 1878 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=0;
			}
#line 4417 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;


#line 4421 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"

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

#line 1883 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"


PRIVATE void p_error(const char *s)
	{
		pars_error((char *)s);
		yyclearin;
	}
	
