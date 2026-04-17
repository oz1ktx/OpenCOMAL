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
  YYSYMBOL_becomesSYM = 6,                 /* becomesSYM  */
  YYSYMBOL_becplusSYM = 7,                 /* becplusSYM  */
  YYSYMBOL_becminusSYM = 8,                /* becminusSYM  */
  YYSYMBOL_caseSYM = 9,                    /* caseSYM  */
  YYSYMBOL_chdirSYM = 10,                  /* chdirSYM  */
  YYSYMBOL_closedSYM = 11,                 /* closedSYM  */
  YYSYMBOL_closeSYM = 12,                  /* closeSYM  */
  YYSYMBOL_colonSYM = 13,                  /* colonSYM  */
  YYSYMBOL_commaSYM = 14,                  /* commaSYM  */
  YYSYMBOL_cursorSYM = 15,                 /* cursorSYM  */
  YYSYMBOL_dataSYM = 16,                   /* dataSYM  */
  YYSYMBOL_delSYM = 17,                    /* delSYM  */
  YYSYMBOL_dimSYM = 18,                    /* dimSYM  */
  YYSYMBOL_dirSYM = 19,                    /* dirSYM  */
  YYSYMBOL_drawSYM = 20,                   /* drawSYM  */
  YYSYMBOL_playSYM = 21,                   /* playSYM  */
  YYSYMBOL_toneSYM = 22,                   /* toneSYM  */
  YYSYMBOL_sleepSYM = 23,                  /* sleepSYM  */
  YYSYMBOL_divideSYM = 24,                 /* divideSYM  */
  YYSYMBOL_divSYM = 25,                    /* divSYM  */
  YYSYMBOL_doSYM = 26,                     /* doSYM  */
  YYSYMBOL_downtoSYM = 27,                 /* downtoSYM  */
  YYSYMBOL_dynamicSYM = 28,                /* dynamicSYM  */
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
  YYSYMBOL_eolnSYM = 40,                   /* eolnSYM  */
  YYSYMBOL_eorSYM = 41,                    /* eorSYM  */
  YYSYMBOL_eqlSYM = 42,                    /* eqlSYM  */
  YYSYMBOL_escSYM = 43,                    /* escSYM  */
  YYSYMBOL_execSYM = 44,                   /* execSYM  */
  YYSYMBOL_exitSYM = 45,                   /* exitSYM  */
  YYSYMBOL_externalSYM = 46,               /* externalSYM  */
  YYSYMBOL_fileSYM = 47,                   /* fileSYM  */
  YYSYMBOL_queueSYM = 48,                  /* queueSYM  */
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
  YYSYMBOL_localSYM = 59,                  /* localSYM  */
  YYSYMBOL_loopSYM = 60,                   /* loopSYM  */
  YYSYMBOL_lparenSYM = 61,                 /* lparenSYM  */
  YYSYMBOL_lssSYM = 62,                    /* lssSYM  */
  YYSYMBOL_minusSYM = 63,                  /* minusSYM  */
  YYSYMBOL_mkdirSYM = 64,                  /* mkdirSYM  */
  YYSYMBOL_modSYM = 65,                    /* modSYM  */
  YYSYMBOL_nameSYM = 66,                   /* nameSYM  */
  YYSYMBOL_neqSYM = 67,                    /* neqSYM  */
  YYSYMBOL_nullSYM = 68,                   /* nullSYM  */
  YYSYMBOL_ofSYM = 69,                     /* ofSYM  */
  YYSYMBOL_openSYM = 70,                   /* openSYM  */
  YYSYMBOL_orSYM = 71,                     /* orSYM  */
  YYSYMBOL_orthenSYM = 72,                 /* orthenSYM  */
  YYSYMBOL_osSYM = 73,                     /* osSYM  */
  YYSYMBOL_otherwiseSYM = 74,              /* otherwiseSYM  */
  YYSYMBOL_pageSYM = 75,                   /* pageSYM  */
  YYSYMBOL_plusSYM = 76,                   /* plusSYM  */
  YYSYMBOL_powerSYM = 77,                  /* powerSYM  */
  YYSYMBOL_printSYM = 78,                  /* printSYM  */
  YYSYMBOL_procSYM = 79,                   /* procSYM  */
  YYSYMBOL_randomSYM = 80,                 /* randomSYM  */
  YYSYMBOL_readSYM = 81,                   /* readSYM  */
  YYSYMBOL_read_onlySYM = 82,              /* read_onlySYM  */
  YYSYMBOL_refSYM = 83,                    /* refSYM  */
  YYSYMBOL_repeatSYM = 84,                 /* repeatSYM  */
  YYSYMBOL_restoreSYM = 85,                /* restoreSYM  */
  YYSYMBOL_retrySYM = 86,                  /* retrySYM  */
  YYSYMBOL_returnSYM = 87,                 /* returnSYM  */
  YYSYMBOL_rmdirSYM = 88,                  /* rmdirSYM  */
  YYSYMBOL_rndSYM = 89,                    /* rndSYM  */
  YYSYMBOL_rparenSYM = 90,                 /* rparenSYM  */
  YYSYMBOL_select_inputSYM = 91,           /* select_inputSYM  */
  YYSYMBOL_select_outputSYM = 92,          /* select_outputSYM  */
  YYSYMBOL_semicolonSYM = 93,              /* semicolonSYM  */
  YYSYMBOL_staticSYM = 94,                 /* staticSYM  */
  YYSYMBOL_stepSYM = 95,                   /* stepSYM  */
  YYSYMBOL_stopSYM = 96,                   /* stopSYM  */
  YYSYMBOL_spawnSYM = 97,                  /* spawnSYM  */
  YYSYMBOL_sysSYM = 98,                    /* sysSYM  */
  YYSYMBOL_syssSYM = 99,                   /* syssSYM  */
  YYSYMBOL_thenSYM = 100,                  /* thenSYM  */
  YYSYMBOL_timesSYM = 101,                 /* timesSYM  */
  YYSYMBOL_toSYM = 102,                    /* toSYM  */
  YYSYMBOL_trapSYM = 103,                  /* trapSYM  */
  YYSYMBOL_unitSYM = 104,                  /* unitSYM  */
  YYSYMBOL_untilSYM = 105,                 /* untilSYM  */
  YYSYMBOL_usingSYM = 106,                 /* usingSYM  */
  YYSYMBOL_whenSYM = 107,                  /* whenSYM  */
  YYSYMBOL_whileSYM = 108,                 /* whileSYM  */
  YYSYMBOL_writeSYM = 109,                 /* writeSYM  */
  YYSYMBOL_qreadSYM = 110,                 /* qreadSYM  */
  YYSYMBOL_qwriteSYM = 111,                /* qwriteSYM  */
  YYSYMBOL_rnSYM = 112,                    /* rnSYM  */
  YYSYMBOL_rsSYM = 113,                    /* rsSYM  */
  YYSYMBOL_tnrnSYM = 114,                  /* tnrnSYM  */
  YYSYMBOL_tnrsSYM = 115,                  /* tnrsSYM  */
  YYSYMBOL_tsrnSYM = 116,                  /* tsrnSYM  */
  YYSYMBOL_tonrsSYM = 117,                 /* tonrsSYM  */
  YYSYMBOL_tsrsSYM = 118,                  /* tsrsSYM  */
  YYSYMBOL_tsrsnSYM = 119,                 /* tsrsnSYM  */
  YYSYMBOL_lenSYM = 120,                   /* lenSYM  */
  YYSYMBOL_floatnumSYM = 121,              /* floatnumSYM  */
  YYSYMBOL_idSYM = 122,                    /* idSYM  */
  YYSYMBOL_intidSYM = 123,                 /* intidSYM  */
  YYSYMBOL_stringidSYM = 124,              /* stringidSYM  */
  YYSYMBOL_intnumSYM = 125,                /* intnumSYM  */
  YYSYMBOL_remSYM = 126,                   /* remSYM  */
  YYSYMBOL_stringSYM = 127,                /* stringSYM  */
  YYSYMBOL_USIGN = 128,                    /* USIGN  */
  YYSYMBOL_YYACCEPT = 129,                 /* $accept  */
  YYSYMBOL_a_comal_line = 130,             /* a_comal_line  */
  YYSYMBOL_comal_line = 131,               /* comal_line  */
  YYSYMBOL_optrem = 132,                   /* optrem  */
  YYSYMBOL_program_line = 133,             /* program_line  */
  YYSYMBOL_complex_stat = 134,             /* complex_stat  */
  YYSYMBOL_simple_stat = 135,              /* simple_stat  */
  YYSYMBOL_complex_1word = 136,            /* complex_1word  */
  YYSYMBOL_simple_1word = 137,             /* simple_1word  */
  YYSYMBOL_case_stat = 138,                /* case_stat  */
  YYSYMBOL_close_stat = 139,               /* close_stat  */
  YYSYMBOL_cursor_stat = 140,              /* cursor_stat  */
  YYSYMBOL_chdir_stat = 141,               /* chdir_stat  */
  YYSYMBOL_rmdir_stat = 142,               /* rmdir_stat  */
  YYSYMBOL_mkdir_stat = 143,               /* mkdir_stat  */
  YYSYMBOL_data_stat = 144,                /* data_stat  */
  YYSYMBOL_draw_stat = 145,                /* draw_stat  */
  YYSYMBOL_tone_stat = 146,                /* tone_stat  */
  YYSYMBOL_play_stat = 147,                /* play_stat  */
  YYSYMBOL_sleep_stat = 148,               /* sleep_stat  */
  YYSYMBOL_del_stat = 149,                 /* del_stat  */
  YYSYMBOL_dir_stat = 150,                 /* dir_stat  */
  YYSYMBOL_unit_stat = 151,                /* unit_stat  */
  YYSYMBOL_local_stat = 152,               /* local_stat  */
  YYSYMBOL_local_list = 153,               /* local_list  */
  YYSYMBOL_local_item = 154,               /* local_item  */
  YYSYMBOL_dim_stat = 155,                 /* dim_stat  */
  YYSYMBOL_dim_list = 156,                 /* dim_list  */
  YYSYMBOL_dim_item = 157,                 /* dim_item  */
  YYSYMBOL_of = 158,                       /* of  */
  YYSYMBOL_opt_dim_ensions = 159,          /* opt_dim_ensions  */
  YYSYMBOL_dim_ensions = 160,              /* dim_ensions  */
  YYSYMBOL_dim_ension_list = 161,          /* dim_ension_list  */
  YYSYMBOL_dim_ension = 162,               /* dim_ension  */
  YYSYMBOL_elif_stat = 163,                /* elif_stat  */
  YYSYMBOL_exit_stat = 164,                /* exit_stat  */
  YYSYMBOL_ifwhen = 165,                   /* ifwhen  */
  YYSYMBOL_exec_stat = 166,                /* exec_stat  */
  YYSYMBOL_spawn_stat = 167,               /* spawn_stat  */
  YYSYMBOL_for_stat = 168,                 /* for_stat  */
  YYSYMBOL_todownto = 169,                 /* todownto  */
  YYSYMBOL_optstep = 170,                  /* optstep  */
  YYSYMBOL_func_stat = 171,                /* func_stat  */
  YYSYMBOL_if_stat = 172,                  /* if_stat  */
  YYSYMBOL_import_stat = 173,              /* import_stat  */
  YYSYMBOL_import_list = 174,              /* import_list  */
  YYSYMBOL_input_stat = 175,               /* input_stat  */
  YYSYMBOL_input_modifier = 176,           /* input_modifier  */
  YYSYMBOL_open_stat = 177,                /* open_stat  */
  YYSYMBOL_open_type = 178,                /* open_type  */
  YYSYMBOL_queue_type = 179,               /* queue_type  */
  YYSYMBOL_os_stat = 180,                  /* os_stat  */
  YYSYMBOL_print_stat = 181,               /* print_stat  */
  YYSYMBOL_printi = 182,                   /* printi  */
  YYSYMBOL_prnum_list = 183,               /* prnum_list  */
  YYSYMBOL_print_list = 184,               /* print_list  */
  YYSYMBOL_pr_sep = 185,                   /* pr_sep  */
  YYSYMBOL_optpr_sep = 186,                /* optpr_sep  */
  YYSYMBOL_proc_stat = 187,                /* proc_stat  */
  YYSYMBOL_read_stat = 188,                /* read_stat  */
  YYSYMBOL_restore_stat = 189,             /* restore_stat  */
  YYSYMBOL_return_stat = 190,              /* return_stat  */
  YYSYMBOL_select_out_stat = 191,          /* select_out_stat  */
  YYSYMBOL_select_in_stat = 192,           /* select_in_stat  */
  YYSYMBOL_stop_stat = 193,                /* stop_stat  */
  YYSYMBOL_sys_stat = 194,                 /* sys_stat  */
  YYSYMBOL_until_stat = 195,               /* until_stat  */
  YYSYMBOL_trap_stat = 196,                /* trap_stat  */
  YYSYMBOL_plusorminus = 197,              /* plusorminus  */
  YYSYMBOL_when_stat = 198,                /* when_stat  */
  YYSYMBOL_when_list = 199,                /* when_list  */
  YYSYMBOL_when_numlist = 200,             /* when_numlist  */
  YYSYMBOL_when_numitem = 201,             /* when_numitem  */
  YYSYMBOL_when_strlist = 202,             /* when_strlist  */
  YYSYMBOL_when_stritem = 203,             /* when_stritem  */
  YYSYMBOL_relop = 204,                    /* relop  */
  YYSYMBOL_while_stat = 205,               /* while_stat  */
  YYSYMBOL_repeat_stat = 206,              /* repeat_stat  */
  YYSYMBOL_write_stat = 207,               /* write_stat  */
  YYSYMBOL_assign_stat = 208,              /* assign_stat  */
  YYSYMBOL_assign_list = 209,              /* assign_list  */
  YYSYMBOL_assign_item = 210,              /* assign_item  */
  YYSYMBOL_nassign = 211,                  /* nassign  */
  YYSYMBOL_sassign = 212,                  /* sassign  */
  YYSYMBOL_assign1 = 213,                  /* assign1  */
  YYSYMBOL_assign2 = 214,                  /* assign2  */
  YYSYMBOL_label_stat = 215,               /* label_stat  */
  YYSYMBOL_xid = 216,                      /* xid  */
  YYSYMBOL_exp = 217,                      /* exp  */
  YYSYMBOL_numexp = 218,                   /* numexp  */
  YYSYMBOL_numexp2 = 219,                  /* numexp2  */
  YYSYMBOL_stringexp = 220,                /* stringexp  */
  YYSYMBOL_stringexp2 = 221,               /* stringexp2  */
  YYSYMBOL_opt_stringexp = 222,            /* opt_stringexp  */
  YYSYMBOL_string_factor = 223,            /* string_factor  */
  YYSYMBOL_opt_arg = 224,                  /* opt_arg  */
  YYSYMBOL_substr_spec = 225,              /* substr_spec  */
  YYSYMBOL_substr_spec2 = 226,             /* substr_spec2  */
  YYSYMBOL_optnumlvalue = 227,             /* optnumlvalue  */
  YYSYMBOL_optexp = 228,                   /* optexp  */
  YYSYMBOL_optid = 229,                    /* optid  */
  YYSYMBOL_optid2 = 230,                   /* optid2  */
  YYSYMBOL_optfile = 231,                  /* optfile  */
  YYSYMBOL_optfileS = 232,                 /* optfileS  */
  YYSYMBOL_lval_list = 233,                /* lval_list  */
  YYSYMBOL_lvalue = 234,                   /* lvalue  */
  YYSYMBOL_numlvalue = 235,                /* numlvalue  */
  YYSYMBOL_numlvalue2 = 236,               /* numlvalue2  */
  YYSYMBOL_strlvalue = 237,                /* strlvalue  */
  YYSYMBOL_strlvalue2 = 238,               /* strlvalue2  */
  YYSYMBOL_file_designator = 239,          /* file_designator  */
  YYSYMBOL_io_designator = 240,            /* io_designator  */
  YYSYMBOL_opt_external = 241,             /* opt_external  */
  YYSYMBOL_procfunc_head = 242,            /* procfunc_head  */
  YYSYMBOL_parmlist = 243,                 /* parmlist  */
  YYSYMBOL_parmitem = 244,                 /* parmitem  */
  YYSYMBOL_oneparm = 245,                  /* oneparm  */
  YYSYMBOL_id = 246,                       /* id  */
  YYSYMBOL_numid = 247,                    /* numid  */
  YYSYMBOL_opt_commalist = 248,            /* opt_commalist  */
  YYSYMBOL_exp_list = 249,                 /* exp_list  */
  YYSYMBOL_optsimple_stat = 250,           /* optsimple_stat  */
  YYSYMBOL_optof = 251,                    /* optof  */
  YYSYMBOL_optdo = 252,                    /* optdo  */
  YYSYMBOL_optthen = 253,                  /* optthen  */
  YYSYMBOL_optread_only = 254,             /* optread_only  */
  YYSYMBOL_optclosed = 255                 /* optclosed  */
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
#define YYFINAL  253
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1612

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  129
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  127
/* YYNRULES -- Number of rules.  */
#define YYNRULES  347
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  564

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   383


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
     125,   126,   127,   128
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   236,   236,   241,   250,   258,   268,   278,   284,   286,
     290,   291,   293,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   350,   351,
     354,   358,   362,   366,   370,   374,   378,   382,   386,   390,
     394,   400,   405,   409,   415,   419,   423,   428,   432,   438,
     445,   450,   457,   465,   472,   479,   486,   493,   515,   523,
     531,   539,   546,   553,   561,   567,   572,   579,   583,   587,
     591,   595,   602,   609,   614,   621,   625,   629,   633,   639,
     640,   643,   645,   650,   656,   661,   668,   674,   680,   688,
     695,   702,   703,   706,   713,   720,   732,   736,   742,   747,
     752,   762,   770,   776,   784,   791,   800,   808,   814,   821,
     826,   833,   842,   848,   854,   860,   868,   874,   882,   889,
     896,   903,   912,   923,   924,   927,   931,   937,   941,   947,
     951,   957,   959,   964,   974,   982,   989,   996,  1004,  1011,
    1018,  1025,  1032,  1039,  1043,  1049,  1056,  1057,  1060,  1065,
    1068,  1072,  1078,  1083,  1086,  1090,  1094,  1100,  1104,  1108,
    1112,  1116,  1120,  1126,  1134,  1142,  1150,  1157,  1162,  1168,
    1172,  1178,  1179,  1182,  1183,  1189,  1193,  1199,  1203,  1209,
    1216,  1220,  1224,  1230,  1231,  1234,  1240,  1244,  1248,  1252,
    1256,  1260,  1264,  1268,  1272,  1276,  1280,  1284,  1288,  1292,
    1296,  1300,  1304,  1308,  1312,  1316,  1320,  1324,  1328,  1332,
    1336,  1340,  1344,  1348,  1352,  1356,  1357,  1361,  1365,  1369,
    1373,  1377,  1381,  1385,  1389,  1393,  1399,  1405,  1409,  1410,
    1416,  1418,  1423,  1424,  1428,  1432,  1436,  1440,  1444,  1448,
    1452,  1456,  1462,  1467,  1472,  1478,  1483,  1488,  1493,  1500,
    1502,  1507,  1509,  1514,  1516,  1521,  1523,  1528,  1535,  1540,
    1541,  1542,  1545,  1549,  1555,  1556,  1559,  1566,  1567,  1571,
    1575,  1581,  1588,  1592,  1596,  1600,  1604,  1610,  1615,  1622,
    1627,  1632,  1637,  1644,  1652,  1660,  1669,  1674,  1679,  1684,
    1689,  1696,  1703,  1710,  1717,  1724,  1733,  1738,  1745,  1746,
    1749,  1750,  1753,  1754,  1757,  1761,  1767,  1778,  1783,  1784,
    1787,  1788,  1791,  1792,  1795,  1800,  1805,  1810
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
  "appendSYM", "becomesSYM", "becplusSYM", "becminusSYM", "caseSYM",
  "chdirSYM", "closedSYM", "closeSYM", "colonSYM", "commaSYM", "cursorSYM",
  "dataSYM", "delSYM", "dimSYM", "dirSYM", "drawSYM", "playSYM", "toneSYM",
  "sleepSYM", "divideSYM", "divSYM", "doSYM", "downtoSYM", "dynamicSYM",
  "elifSYM", "elseSYM", "endcaseSYM", "endforSYM", "endfuncSYM",
  "endifSYM", "endloopSYM", "endprocSYM", "endSYM", "endtrapSYM",
  "endwhileSYM", "eolnSYM", "eorSYM", "eqlSYM", "escSYM", "execSYM",
  "exitSYM", "externalSYM", "fileSYM", "queueSYM", "forSYM", "funcSYM",
  "geqSYM", "gtrSYM", "handlerSYM", "ifSYM", "importSYM", "inputSYM",
  "inSYM", "leqSYM", "localSYM", "loopSYM", "lparenSYM", "lssSYM",
  "minusSYM", "mkdirSYM", "modSYM", "nameSYM", "neqSYM", "nullSYM",
  "ofSYM", "openSYM", "orSYM", "orthenSYM", "osSYM", "otherwiseSYM",
  "pageSYM", "plusSYM", "powerSYM", "printSYM", "procSYM", "randomSYM",
  "readSYM", "read_onlySYM", "refSYM", "repeatSYM", "restoreSYM",
  "retrySYM", "returnSYM", "rmdirSYM", "rndSYM", "rparenSYM",
  "select_inputSYM", "select_outputSYM", "semicolonSYM", "staticSYM",
  "stepSYM", "stopSYM", "spawnSYM", "sysSYM", "syssSYM", "thenSYM",
  "timesSYM", "toSYM", "trapSYM", "unitSYM", "untilSYM", "usingSYM",
  "whenSYM", "whileSYM", "writeSYM", "qreadSYM", "qwriteSYM", "rnSYM",
  "rsSYM", "tnrnSYM", "tnrsSYM", "tsrnSYM", "tonrsSYM", "tsrsSYM",
  "tsrsnSYM", "lenSYM", "floatnumSYM", "idSYM", "intidSYM", "stringidSYM",
  "intnumSYM", "remSYM", "stringSYM", "USIGN", "$accept", "a_comal_line",
  "comal_line", "optrem", "program_line", "complex_stat", "simple_stat",
  "complex_1word", "simple_1word", "case_stat", "close_stat",
  "cursor_stat", "chdir_stat", "rmdir_stat", "mkdir_stat", "data_stat",
  "draw_stat", "tone_stat", "play_stat", "sleep_stat", "del_stat",
  "dir_stat", "unit_stat", "local_stat", "local_list", "local_item",
  "dim_stat", "dim_list", "dim_item", "of", "opt_dim_ensions",
  "dim_ensions", "dim_ension_list", "dim_ension", "elif_stat", "exit_stat",
  "ifwhen", "exec_stat", "spawn_stat", "for_stat", "todownto", "optstep",
  "func_stat", "if_stat", "import_stat", "import_list", "input_stat",
  "input_modifier", "open_stat", "open_type", "queue_type", "os_stat",
  "print_stat", "printi", "prnum_list", "print_list", "pr_sep",
  "optpr_sep", "proc_stat", "read_stat", "restore_stat", "return_stat",
  "select_out_stat", "select_in_stat", "stop_stat", "sys_stat",
  "until_stat", "trap_stat", "plusorminus", "when_stat", "when_list",
  "when_numlist", "when_numitem", "when_strlist", "when_stritem", "relop",
  "while_stat", "repeat_stat", "write_stat", "assign_stat", "assign_list",
  "assign_item", "nassign", "sassign", "assign1", "assign2", "label_stat",
  "xid", "exp", "numexp", "numexp2", "stringexp", "stringexp2",
  "opt_stringexp", "string_factor", "opt_arg", "substr_spec",
  "substr_spec2", "optnumlvalue", "optexp", "optid", "optid2", "optfile",
  "optfileS", "lval_list", "lvalue", "numlvalue", "numlvalue2",
  "strlvalue", "strlvalue2", "file_designator", "io_designator",
  "opt_external", "procfunc_head", "parmlist", "parmitem", "oneparm", "id",
  "numid", "opt_commalist", "exp_list", "optsimple_stat", "optof", "optdo",
  "optthen", "optread_only", "optclosed", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-369)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-81)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     630,    31,  1485,   183,    14,  1485,  1485,   183,    97,   183,
    1485,  1485,  1485,  1485,  1485,  -369,  -369,    81,   123,  -369,
    -369,   -67,  -369,  -369,  -369,   -63,   -18,    81,   123,  -369,
    1485,   123,    -9,   127,  -369,   183,  -369,    57,   183,  -369,
    -369,  -369,   -47,    61,   867,   -67,  -369,  1485,   183,   183,
     183,  -369,  1485,   -63,  1485,    50,   183,  1485,  1255,  1485,
      61,    35,    20,    84,   752,  -369,   120,   126,  -369,    71,
      71,  -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,
    -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,
    -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,
    -369,  1420,  -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,
    -369,  -369,  -369,  -369,  -369,  -369,  -369,   114,  -369,  -369,
     -26,   175,  -369,   188,  -369,  -369,  1485,  1485,  1485,   161,
     173,   176,  -369,  -369,   179,   191,   193,   197,   199,   203,
     214,  -369,   216,  -369,  -369,  -369,   211,  -369,  1263,  -369,
    1021,   223,  -369,  -369,   183,  -369,    10,  -369,  -369,  1485,
     281,  1021,  -369,   285,  -369,  -369,  -369,   124,   289,  -369,
     247,  -369,  -369,   285,   285,   285,   285,   209,  -369,  -369,
    -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,  1485,
      46,   251,   209,   299,  -369,    38,  1485,  1485,   301,   147,
    -369,   140,   302,  -369,   247,  -369,  1485,  1485,  -369,   251,
    1485,   147,  -369,  -369,    50,   210,  -369,  -369,  -369,  -369,
    -369,  -369,  -369,  -369,   285,    22,  -369,  -369,  -369,  -369,
    -369,   183,  -369,  -369,  -369,  -369,   303,  -369,   304,  -369,
    1485,  -369,  -369,   293,  1485,  -369,  1485,  1485,   415,  -369,
      71,  -369,  -369,  -369,  -369,  -369,  -369,   183,     2,  -369,
    1485,   147,  -369,  -369,  -369,  -369,  1485,  -369,  -369,  -369,
     183,  -369,   999,   221,  -369,  -369,  1485,  1485,  1485,  1485,
    1485,   183,  1485,  -369,   183,  1485,  1485,  -369,  -369,  1485,
    1485,  1485,  1485,  1485,  1485,  1485,  1485,  1485,  1485,  1485,
    1485,  1485,  1485,  1485,  1485,  1485,  1485,   183,   183,   183,
     183,   183,   183,   183,   183,  1485,   415,  -369,   134,   285,
    1485,  1485,  1485,  1485,   -44,    97,  -369,  -369,  -369,  -369,
    1485,   109,   309,   867,   123,   123,  -369,   229,   276,  -369,
     307,  -369,  -369,  -369,  1485,   -44,   127,  -369,  -369,   310,
     311,   309,   279,   307,  1485,  -369,  -369,  -369,  -369,  1339,
    1290,  -369,  -369,  -369,   867,   285,    16,    26,    32,    36,
    1485,   313,   238,    52,    54,  -369,   316,  -369,  -369,  1485,
    -369,     2,  -369,  -369,  -369,  -369,  -369,   943,    56,    59,
    1043,  1087,   137,  1131,   138,    66,  1175,   360,    85,    85,
     253,   253,    85,    88,    88,    88,    88,    88,    90,   253,
      88,    85,    85,    90,   253,   253,    10,    10,    10,  -369,
      10,    10,    10,   223,   253,   313,  -369,  -369,    73,  -369,
     228,  -369,  -369,  -369,  1485,  -369,    15,   123,   123,   215,
     123,    83,  -369,  -369,   270,  -369,    93,  -369,  -369,  -369,
     299,    89,  -369,  1485,  -369,  1485,   147,  -369,  1485,  -369,
     183,   183,    93,  -369,  1485,  -369,  -369,  1485,  -369,   183,
    -369,  -369,  -369,  -369,  -369,  -369,   319,  1485,  -369,  -369,
     223,  1485,  -369,  1485,  1485,  -369,  -369,  -369,  -369,  -369,
    -369,  -369,  -369,  -369,  -369,  -369,  1485,  -369,  1485,  1485,
    -369,  -369,  -369,  1485,  -369,  -369,  -369,  -369,   109,  -369,
     292,   183,   294,  -369,  -369,   330,   332,  -369,  -369,   333,
     334,  -369,   337,  -369,  -369,  -369,     2,  -369,  1219,  -369,
    -369,  -369,   256,  -369,   183,  -369,   183,  -369,  -369,    21,
      96,  -369,  1485,  -369,  -369,  1485,   293,  -369,  -369,  -369,
    1485,  -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,   867,
     264,  -369,  -369,  -369
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,     0,     0,     0,   291,     0,     0,     0,     0,   261,
       0,     0,     0,     0,     0,    60,    61,   280,   284,    63,
      65,   286,    75,    73,    67,     0,    76,     0,     0,    72,
       0,     0,   139,     0,    64,     0,    74,     0,     0,    69,
      77,   153,     0,   288,    70,   286,    78,   282,     0,     0,
       0,   154,   282,     0,     0,    71,     0,     0,     0,     0,
       0,   210,   298,   302,    12,     8,     0,     0,     7,     9,
       9,    27,    59,    13,    28,    30,    29,    45,    38,    14,
      22,    53,    52,    46,    31,    33,    55,    34,    32,    15,
      16,    35,    47,    17,    18,    19,    36,    37,    39,    40,
      41,   149,    20,    42,    43,    44,    48,    49,    50,    51,
      21,    54,    23,    24,    25,    56,    58,   196,   198,    26,
     297,     0,   296,     0,   301,     3,     0,     0,     0,   250,
       0,     0,   253,   266,     0,     0,     0,   273,     0,     0,
       0,   244,   210,   243,   268,   297,   339,   213,   215,   214,
     256,   258,   245,   262,     0,    83,   256,   289,   290,     0,
       0,     0,   335,    86,    91,   330,   331,     0,   102,   104,
       0,   260,    92,    87,    89,    88,    90,   343,    68,   279,
     329,    62,   283,   328,   285,    66,   123,   121,   122,     0,
       0,   318,   343,   133,   135,   326,     0,     0,     0,     0,
     137,    98,    94,    96,   112,    85,     0,     0,   148,   318,
       0,     0,   287,    76,     0,     0,   165,   281,   166,    84,
     168,   167,   169,   124,   170,     0,    93,   171,   189,   191,
     187,     0,   192,   188,   190,   175,   176,   179,   177,   183,
       0,   181,   185,   341,     0,   209,   333,   333,   333,   304,
       9,    10,    11,     1,     2,     5,     6,     0,   162,   158,
       0,     0,   206,   207,   208,   205,     0,   201,   202,   204,
       0,   203,     0,     0,   241,   242,     0,     0,     0,     0,
       0,     0,     0,   267,     0,     0,     0,   338,    79,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   263,     0,    81,
       0,     0,     0,     0,   108,     0,   105,   342,   119,   120,
       0,     0,   347,   337,     0,     0,   333,     0,     0,   138,
     136,   293,   294,   295,     0,   101,     0,    97,   111,     0,
       0,   347,     0,   164,     0,   174,   173,   172,   186,     0,
       0,   180,   184,   340,   337,   195,     0,     0,     0,     0,
       0,   213,     0,     0,     0,     4,     0,   159,   160,   161,
     150,   152,   197,   199,   200,   255,   271,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   222,   223,
     230,   232,   226,   216,   221,   219,   220,   218,   228,   233,
     217,   224,   225,   227,   231,   229,   234,   239,   237,   240,
     238,   236,   235,   257,   259,     0,    82,   334,     0,   115,
     116,   106,   109,   110,     0,   103,     0,     0,     0,     0,
       0,     0,   320,   321,   326,   346,   316,   336,   131,   134,
     132,     0,   309,     0,   311,     0,     0,    99,     0,    95,
       0,     0,   316,   307,     0,   194,   178,     0,   182,     0,
     193,   332,   212,   211,   300,   299,   276,   277,   274,   306,
     303,     0,   157,     0,     0,   251,   254,   269,   249,   264,
     246,   272,   265,   270,   248,   247,     0,   113,     0,     0,
     107,   127,   126,     0,   325,   323,   324,   322,     0,   317,
       0,     0,     0,   130,   327,     0,     0,   292,   100,     0,
       0,   163,     0,   278,   275,   305,   162,   156,     0,   114,
     118,   117,   129,   319,     0,   313,     0,   310,   312,     0,
       0,   308,   161,   151,   252,     0,   341,   314,   315,   144,
       0,   142,   143,   140,   146,   147,   141,   155,   128,   337,
     345,   125,   344,   145
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -369,  -369,  -369,   -60,  -369,   288,   154,  -369,  -369,  -369,
    -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,
    -369,  -369,  -369,  -369,  -369,     8,  -369,  -369,    30,    11,
    -369,  -110,  -369,  -139,  -369,  -369,  -369,  -369,  -369,  -369,
    -369,  -369,  -369,  -369,  -369,    23,  -369,  -369,  -369,  -369,
    -369,  -369,  -369,  -369,  -369,    99,  -368,  -166,  -369,  -369,
    -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,
    -369,  -369,    12,  -369,    17,   -54,  -369,  -369,  -369,  -369,
    -369,   100,  -369,  -369,   -49,  -369,  -369,     3,     6,    19,
     320,    34,   122,  -369,    58,  -369,   -59,  -369,  -369,   322,
    -369,   331,  -369,  -369,   164,   -76,   -15,     0,  -188,     1,
     321,   282,   -78,   177,  -369,  -121,  -302,   -13,    -2,  -213,
       9,  -357,  -369,  -158,   198,  -369,    40
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    66,    67,    68,   250,    69,   447,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,   202,   203,    88,   168,   169,   434,
     347,   324,   428,   429,    89,    90,   189,    91,    92,    93,
     503,   546,    94,    95,    96,   193,    97,   199,    98,   553,
     556,    99,   100,   101,   526,   258,   379,   380,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   357,   112,
     235,   236,   237,   238,   239,   240,   113,   114,   115,   116,
     117,   118,   266,   270,   267,   268,   119,   145,   162,   147,
     148,   149,   161,   172,   151,   283,   317,   372,   178,   218,
     181,   185,   211,   159,   340,   341,   121,   152,   123,   153,
     212,   200,   513,   332,   441,   442,   194,   444,   183,   366,
     163,   448,   288,   364,   328,   563,   446
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     122,   124,   179,   120,   249,   182,   170,   470,   146,   255,
     256,   343,   190,   483,   -57,   191,   377,   122,   195,   173,
     174,   175,   176,   343,   160,   432,   549,   122,   186,   443,
     471,   204,   449,   177,   368,   373,   187,   155,   196,   197,
     321,   164,   501,   171,   122,   124,   471,   120,   245,   192,
     321,   335,   262,   217,   -80,   184,   223,   433,   217,   142,
     326,   157,   158,   224,   122,   124,   471,   120,   321,   205,
     321,   125,   208,   321,   271,   209,   227,   241,   243,   -57,
     321,   247,   219,   220,   221,   355,   314,   496,   265,   188,
     226,   345,   242,   225,   348,   378,   246,   508,   356,   336,
     -57,   550,   551,   471,   206,   207,   472,   259,   210,   291,
     292,   315,   291,   292,   291,   292,   473,   502,   198,   -80,
     253,   510,   474,   451,   150,   156,   475,   294,   150,   156,
     552,   156,   150,   150,   150,   150,   295,   296,   507,   511,
     -80,   330,   479,   297,   480,   248,   486,   298,   299,   487,
     300,   299,   301,   300,    70,   300,   493,   156,   542,   437,
     156,   304,   305,   497,   304,   305,   254,   305,   319,   150,
     156,   156,   156,   509,   150,   438,   150,   554,   156,   514,
     150,   262,   263,   264,   342,   322,   306,   512,   439,   306,
     375,   306,   440,   323,   262,   269,   342,    65,   215,   122,
     124,   322,   561,   142,    62,   555,   443,   261,   329,   344,
     314,   122,   124,   314,   314,   337,   338,   265,   252,   165,
     166,   167,   276,   150,   386,   349,   350,   490,   492,   352,
     265,   165,   166,   180,   277,   315,   498,   278,   315,   315,
     279,   499,   452,   453,   154,   165,   166,   180,   273,   165,
     166,   201,   280,   365,   281,   367,   369,   374,   282,   361,
     284,   122,   124,   307,   285,   358,   259,   371,   343,   142,
      62,    63,   308,   309,   362,   286,   318,   246,   310,   311,
     287,   150,   131,   312,   316,   383,   388,   389,   313,   454,
     455,   376,   463,   464,   395,   320,   133,   314,   135,   321,
     137,   138,   139,   325,   384,   467,   469,    63,   322,   327,
     144,   386,   331,   334,   339,   354,   346,   359,   360,   363,
     445,   456,   315,   170,   460,   461,   477,   427,   478,   481,
     305,   336,   523,   122,   124,   425,   120,   506,   534,   426,
     536,   430,   431,   537,   204,   538,   562,   539,   540,   436,
     541,   545,   251,   156,   459,   435,   458,   529,   450,   381,
     543,   382,   150,   457,   122,   124,   150,   120,   150,   150,
     150,   466,   423,   465,   222,   353,   216,   468,   241,   156,
     517,   244,   150,   260,   521,   482,   351,   533,   559,   476,
     333,   462,   156,     0,   242,     0,     0,     0,     0,   150,
     150,     0,   307,   392,     0,     0,   394,   150,   397,     0,
       0,   308,   309,     0,     0,     0,     0,   310,   311,     0,
       0,   525,   312,     0,   504,   505,     0,   313,   370,   416,
     417,   418,   419,   420,   421,   422,   314,     0,     0,     0,
       0,   342,     0,   150,     0,     0,   272,   274,   275,     0,
     495,     0,     0,   500,     0,     0,   122,   124,     0,     0,
       0,   315,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   515,     0,   516,     0,   126,   518,   127,     0,
       0,     0,   156,   522,     0,     0,   361,     0,     0,   482,
       0,   128,     0,     0,   519,   520,   524,     0,     0,     0,
     527,   150,     0,   362,   129,     0,     0,     0,     0,     0,
       0,     0,     0,   130,   131,   430,     0,   530,   531,     0,
       0,     0,   532,     0,     0,     0,     0,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,    62,    63,
     143,     0,   144,     0,     0,   535,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   122,
     124,   557,   120,     0,   558,     0,     0,     0,   547,   560,
     548,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   156,   156,     0,     0,     0,     0,     0,     0,
       0,   156,     0,     0,     0,     0,   387,     0,     0,   390,
     391,     0,   393,     0,     0,   150,   396,     0,     0,   398,
     399,   400,   401,   402,   403,   404,   405,   406,   407,   408,
     409,   410,   411,   412,   413,   414,   415,     0,     0,     0,
       0,     1,     0,   156,     0,   424,     0,     0,     0,     2,
       3,     0,     4,     0,     0,     5,     6,     7,     8,     9,
      10,    11,    12,    13,     0,     0,   156,     0,   156,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      -9,     0,     0,     0,    25,    26,     0,     0,     0,    27,
      28,     0,     0,    29,    30,    31,    32,     0,     0,    33,
      34,     0,     0,     0,    35,     0,     0,     0,    36,     0,
      37,     0,     0,    38,    39,    40,     0,     0,    41,    42,
       0,    43,     0,     0,    44,    45,    46,    47,    48,     0,
       0,    49,    50,    51,     0,     0,    52,    53,    54,     0,
       0,     0,     0,    55,    56,    57,     0,    58,    59,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    61,    62,    63,    64,    65,     0,     0,     0,
       0,     2,     3,     0,     4,     0,     0,     5,     6,     7,
       8,     9,    10,    11,    12,    13,     0,     0,     0,     0,
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,     0,     0,     0,     0,    25,    26,     0,     0,
       0,    27,    28,     0,   528,    29,    30,    31,    32,     0,
       0,    33,    34,     0,     0,     0,    35,     0,     0,     0,
      36,     0,    37,     0,     0,    38,    39,    40,     0,     0,
      41,    42,     0,    43,     0,     0,    44,    45,    46,    47,
      48,     0,     0,    49,    50,    51,     0,     0,    52,    53,
      54,     0,     0,     0,     0,    55,    56,    57,     0,    58,
      59,    60,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,    62,    63,     3,     0,     4,
       0,     0,     5,     0,     7,     8,     9,     0,    11,    12,
      13,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    22,     0,     0,     0,     0,     0,
       0,    25,   213,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    31,    32,     0,     0,    33,     0,     0,     0,
       0,    35,     0,     0,     0,    36,     0,    37,     0,     0,
      38,     0,    40,     0,     0,    41,   289,   290,    43,     0,
       0,     0,    45,    46,    47,    48,     0,   484,    49,    50,
      51,     0,     0,    52,    53,    54,     0,   291,   292,     0,
     214,    56,     0,     0,     0,     0,    60,     0,     0,     0,
       0,     0,     0,     0,   293,   294,     0,     0,     0,   142,
      62,    63,     0,     0,   295,   296,     0,     0,     0,     0,
       0,   297,   289,   290,     0,   298,   299,     0,   300,     0,
     301,     0,     0,     0,   302,   303,     0,     0,     0,   304,
     305,     0,     0,   291,   292,     0,     0,     0,     0,     0,
       0,     0,     0,   485,     0,     0,     0,     0,     0,     0,
     293,   294,     0,     0,   306,     0,   289,   290,     0,     0,
     295,   296,     0,     0,     0,     0,     0,   297,     0,     0,
       0,   298,   299,   307,   300,     0,   301,   291,   292,     0,
     302,   303,   308,   309,     0,   304,   305,     0,   310,   311,
       0,     0,     0,   312,   293,   294,     0,     0,   313,   385,
     289,   290,     0,     0,   295,   296,     0,   314,     0,     0,
     306,   297,     0,     0,     0,   298,   299,     0,   300,     0,
     301,   291,   292,     0,   302,   303,     0,     0,     0,   304,
     305,     0,   315,     0,     0,     0,     0,     0,   293,   294,
       0,     0,     0,   488,   289,   290,     0,     0,   295,   296,
       0,     0,     0,     0,   306,   297,     0,     0,     0,   298,
     299,     0,   300,     0,   301,   291,   292,     0,   302,   303,
       0,     0,     0,   304,   305,     0,     0,     0,     0,     0,
       0,     0,   293,   294,     0,     0,     0,   489,   289,   290,
       0,     0,   295,   296,     0,     0,     0,     0,   306,   297,
       0,     0,     0,   298,   299,     0,   300,     0,   301,   291,
     292,     0,   302,   303,     0,     0,     0,   304,   305,     0,
       0,     0,     0,     0,     0,     0,   293,   294,     0,     0,
       0,   491,   289,   290,     0,     0,   295,   296,     0,     0,
       0,     0,   306,   297,     0,     0,     0,   298,   299,     0,
     300,     0,   301,   291,   292,     0,   302,   303,     0,     0,
       0,   304,   305,     0,     0,     0,     0,     0,     0,     0,
     293,   294,     0,     0,     0,   494,   289,   290,     0,     0,
     295,   296,     0,     0,     0,     0,   306,   297,     0,     0,
       0,   298,   299,     0,   300,     0,   301,   291,   292,     0,
     302,   303,     0,     0,     0,   304,   305,   228,     0,     0,
       0,     0,     0,     0,   293,   294,   229,   230,     0,   544,
       0,     0,   231,   232,   295,   296,   126,   233,   127,     0,
     306,   297,   234,     0,     0,   298,   299,     0,   300,     0,
     301,   128,   228,     0,   302,   303,     0,     0,     0,   304,
     305,   229,   230,     0,   129,     0,     0,   231,   232,     0,
       0,   154,   233,   130,   131,     0,     0,   234,     0,     0,
       0,     0,     0,     0,   306,     0,     0,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,    62,    63,
     143,   228,   144,     0,     0,     0,     0,     0,     0,   131,
     229,   230,     0,     0,     0,     0,     0,   232,     0,     0,
     126,   233,   127,   133,     0,   135,   234,   137,   138,   139,
       0,     0,     0,     0,    63,   128,     0,   144,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   129,     0,
       0,     0,     0,     0,     0,     0,     0,   130,   131,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,    62,    63,   143,     0,   144,   196,   197,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   126,     0,   127,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   128,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   129,
       0,     0,     0,     0,     0,     0,     0,     0,   130,   131,
       0,     0,     0,     0,     0,     0,   257,     0,     0,     0,
       0,     0,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,    62,    63,   143,   126,   144,   127,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   128,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   129,     0,     0,     0,     0,     0,
       0,     0,     0,   130,   131,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,    62,    63,
     143,     0,   144
};

static const yytype_int16 yycheck[] =
{
       0,     0,    17,     0,    63,    18,     8,   364,     2,    69,
      70,   199,    27,   381,    40,    28,    14,    17,    31,    10,
      11,    12,    13,   211,     5,    69,     5,    27,    25,   331,
      14,    33,   334,    14,   247,   248,    54,     3,    47,    48,
      14,     7,    27,     9,    44,    44,    14,    44,    13,    30,
      14,    13,     6,    47,    40,   122,    53,   101,    52,   122,
     170,    47,    48,    54,    64,    64,    14,    64,    14,    35,
      14,    40,    38,    14,   123,   122,    57,    58,    59,   105,
      14,    61,    48,    49,    50,    63,    76,    14,    42,   107,
      56,   201,    58,    43,   204,    93,    61,    14,    76,    61,
     126,    80,    81,    14,    47,    48,    90,   101,    47,    24,
      25,   101,    24,    25,    24,    25,    90,   102,   127,   105,
       0,    28,    90,   336,     2,     3,    90,    42,     6,     7,
     109,     9,    10,    11,    12,    13,    51,    52,   440,    46,
     126,   190,    90,    58,    90,    61,    90,    62,    63,    90,
      65,    63,    67,    65,     0,    65,    90,    35,   526,    50,
      38,    76,    77,    90,    76,    77,    40,    77,   159,    47,
      48,    49,    50,    90,    52,    66,    54,    81,    56,    90,
      58,     6,     7,     8,   199,    61,   101,    94,    79,   101,
     250,   101,    83,    69,     6,     7,   211,   126,    44,   199,
     199,    61,   559,   122,   123,   109,   508,    93,   189,    69,
      76,   211,   211,    76,    76,   196,   197,    42,    64,   122,
     123,   124,    61,   101,    90,   206,   207,    90,    90,   210,
      42,   122,   123,   124,    61,   101,     8,    61,   101,   101,
      61,    13,    13,    14,    61,   122,   123,   124,   126,   122,
     123,   124,    61,   244,    61,   246,   247,   248,    61,   240,
      61,   261,   261,    42,    61,   231,   260,   248,   456,   122,
     123,   124,    51,    52,   240,    61,   154,    61,    57,    58,
      69,   159,    99,    62,    61,   266,   277,   278,    67,    13,
      14,   257,    13,    14,   285,    14,   113,    76,   115,    14,
     117,   118,   119,    14,   270,   359,   360,   124,    61,   100,
     127,    90,    61,    14,    13,   105,    14,    14,    14,    26,
      11,    14,   101,   325,    14,    14,    13,   321,    90,    13,
      77,    61,    13,   333,   333,   316,   333,   122,    46,   320,
      46,   322,   323,    13,   346,    13,    82,    14,    14,   330,
      13,    95,    64,   231,   346,   325,   345,   496,   335,   260,
     526,   261,   240,   344,   364,   364,   244,   364,   246,   247,
     248,   359,   314,   354,    52,   211,    45,   360,   359,   257,
     456,    60,   260,   101,   462,   379,   209,   508,   546,   370,
     192,   351,   270,    -1,   360,    -1,    -1,    -1,    -1,   277,
     278,    -1,    42,   281,    -1,    -1,   284,   285,   286,    -1,
      -1,    51,    52,    -1,    -1,    -1,    -1,    57,    58,    -1,
      -1,   480,    62,    -1,   437,   438,    -1,    67,    13,   307,
     308,   309,   310,   311,   312,   313,    76,    -1,    -1,    -1,
      -1,   456,    -1,   321,    -1,    -1,   126,   127,   128,    -1,
      90,    -1,    -1,   434,    -1,    -1,   456,   456,    -1,    -1,
      -1,   101,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   453,    -1,   455,    -1,    61,   458,    63,    -1,
      -1,    -1,   360,   464,    -1,    -1,   467,    -1,    -1,   483,
      -1,    76,    -1,    -1,   460,   461,   477,    -1,    -1,    -1,
     481,   379,    -1,   469,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    98,    99,   496,    -1,   498,   499,    -1,
      -1,    -1,   503,    -1,    -1,    -1,    -1,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,    -1,   127,    -1,    -1,   511,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   559,
     559,   542,   559,    -1,   545,    -1,    -1,    -1,   534,   550,
     536,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   460,   461,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   469,    -1,    -1,    -1,    -1,   276,    -1,    -1,   279,
     280,    -1,   282,    -1,    -1,   483,   286,    -1,    -1,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,    -1,    -1,    -1,
      -1,     1,    -1,   511,    -1,   315,    -1,    -1,    -1,     9,
      10,    -1,    12,    -1,    -1,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    -1,    -1,   534,    -1,   536,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    -1,    -1,    -1,    44,    45,    -1,    -1,    -1,    49,
      50,    -1,    -1,    53,    54,    55,    56,    -1,    -1,    59,
      60,    -1,    -1,    -1,    64,    -1,    -1,    -1,    68,    -1,
      70,    -1,    -1,    73,    74,    75,    -1,    -1,    78,    79,
      -1,    81,    -1,    -1,    84,    85,    86,    87,    88,    -1,
      -1,    91,    92,    93,    -1,    -1,    96,    97,    98,    -1,
      -1,    -1,    -1,   103,   104,   105,    -1,   107,   108,   109,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   122,   123,   124,   125,   126,    -1,    -1,    -1,
      -1,     9,    10,    -1,    12,    -1,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    -1,    -1,    -1,    -1,
      -1,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    -1,    -1,    -1,    -1,    44,    45,    -1,    -1,
      -1,    49,    50,    -1,   484,    53,    54,    55,    56,    -1,
      -1,    59,    60,    -1,    -1,    -1,    64,    -1,    -1,    -1,
      68,    -1,    70,    -1,    -1,    73,    74,    75,    -1,    -1,
      78,    79,    -1,    81,    -1,    -1,    84,    85,    86,    87,
      88,    -1,    -1,    91,    92,    93,    -1,    -1,    96,    97,
      98,    -1,    -1,    -1,    -1,   103,   104,   105,    -1,   107,
     108,   109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   122,   123,   124,    10,    -1,    12,
      -1,    -1,    15,    -1,    17,    18,    19,    -1,    21,    22,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,
      -1,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    56,    -1,    -1,    59,    -1,    -1,    -1,
      -1,    64,    -1,    -1,    -1,    68,    -1,    70,    -1,    -1,
      73,    -1,    75,    -1,    -1,    78,     3,     4,    81,    -1,
      -1,    -1,    85,    86,    87,    88,    -1,    14,    91,    92,
      93,    -1,    -1,    96,    97,    98,    -1,    24,    25,    -1,
     103,   104,    -1,    -1,    -1,    -1,   109,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,   122,
     123,   124,    -1,    -1,    51,    52,    -1,    -1,    -1,    -1,
      -1,    58,     3,     4,    -1,    62,    63,    -1,    65,    -1,
      67,    -1,    -1,    -1,    71,    72,    -1,    -1,    -1,    76,
      77,    -1,    -1,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    90,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    42,    -1,    -1,   101,    -1,     3,     4,    -1,    -1,
      51,    52,    -1,    -1,    -1,    -1,    -1,    58,    -1,    -1,
      -1,    62,    63,    42,    65,    -1,    67,    24,    25,    -1,
      71,    72,    51,    52,    -1,    76,    77,    -1,    57,    58,
      -1,    -1,    -1,    62,    41,    42,    -1,    -1,    67,    90,
       3,     4,    -1,    -1,    51,    52,    -1,    76,    -1,    -1,
     101,    58,    -1,    -1,    -1,    62,    63,    -1,    65,    -1,
      67,    24,    25,    -1,    71,    72,    -1,    -1,    -1,    76,
      77,    -1,   101,    -1,    -1,    -1,    -1,    -1,    41,    42,
      -1,    -1,    -1,    90,     3,     4,    -1,    -1,    51,    52,
      -1,    -1,    -1,    -1,   101,    58,    -1,    -1,    -1,    62,
      63,    -1,    65,    -1,    67,    24,    25,    -1,    71,    72,
      -1,    -1,    -1,    76,    77,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    42,    -1,    -1,    -1,    90,     3,     4,
      -1,    -1,    51,    52,    -1,    -1,    -1,    -1,   101,    58,
      -1,    -1,    -1,    62,    63,    -1,    65,    -1,    67,    24,
      25,    -1,    71,    72,    -1,    -1,    -1,    76,    77,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,
      -1,    90,     3,     4,    -1,    -1,    51,    52,    -1,    -1,
      -1,    -1,   101,    58,    -1,    -1,    -1,    62,    63,    -1,
      65,    -1,    67,    24,    25,    -1,    71,    72,    -1,    -1,
      -1,    76,    77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    42,    -1,    -1,    -1,    90,     3,     4,    -1,    -1,
      51,    52,    -1,    -1,    -1,    -1,   101,    58,    -1,    -1,
      -1,    62,    63,    -1,    65,    -1,    67,    24,    25,    -1,
      71,    72,    -1,    -1,    -1,    76,    77,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    42,    51,    52,    -1,    90,
      -1,    -1,    57,    58,    51,    52,    61,    62,    63,    -1,
     101,    58,    67,    -1,    -1,    62,    63,    -1,    65,    -1,
      67,    76,    42,    -1,    71,    72,    -1,    -1,    -1,    76,
      77,    51,    52,    -1,    89,    -1,    -1,    57,    58,    -1,
      -1,    61,    62,    98,    99,    -1,    -1,    67,    -1,    -1,
      -1,    -1,    -1,    -1,   101,    -1,    -1,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,    42,   127,    -1,    -1,    -1,    -1,    -1,    -1,    99,
      51,    52,    -1,    -1,    -1,    -1,    -1,    58,    -1,    -1,
      61,    62,    63,   113,    -1,   115,    67,   117,   118,   119,
      -1,    -1,    -1,    -1,   124,    76,    -1,   127,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,    99,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,    -1,   127,    47,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    61,    -1,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,    99,
      -1,    -1,    -1,    -1,    -1,    -1,   106,    -1,    -1,    -1,
      -1,    -1,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,    61,   127,    63,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    98,    99,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,    -1,   127
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     9,    10,    12,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    44,    45,    49,    50,    53,
      54,    55,    56,    59,    60,    64,    68,    70,    73,    74,
      75,    78,    79,    81,    84,    85,    86,    87,    88,    91,
      92,    93,    96,    97,    98,   103,   104,   105,   107,   108,
     109,   122,   123,   124,   125,   126,   130,   131,   132,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   155,   163,
     164,   166,   167,   168,   171,   172,   173,   175,   177,   180,
     181,   182,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   198,   205,   206,   207,   208,   209,   210,   215,
     216,   235,   236,   237,   238,    40,    61,    63,    76,    89,
      98,    99,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   125,   127,   216,   217,   218,   219,   220,
     221,   223,   236,   238,    61,   220,   221,    47,    48,   232,
     218,   221,   217,   249,   220,   122,   123,   124,   156,   157,
     247,   220,   222,   249,   249,   249,   249,   218,   227,   235,
     124,   229,   246,   247,   122,   230,   216,    54,   107,   165,
     235,   246,   218,   174,   245,   246,    47,    48,   127,   176,
     240,   124,   153,   154,   247,   220,    47,    48,   220,   122,
      47,   231,   239,    45,   103,   135,   230,   217,   228,   220,
     220,   220,   228,   216,   249,    43,   220,   218,    42,    51,
      52,    57,    58,    62,    67,   199,   200,   201,   202,   203,
     204,   218,   220,   218,   239,    13,    61,    61,    61,   225,
     133,   134,   135,     0,    40,   132,   132,   106,   184,   217,
     240,    93,     6,     7,     8,    42,   211,   213,   214,     7,
     212,   213,   219,   221,   219,   219,    61,    61,    61,    61,
      61,    61,    61,   224,    61,    61,    61,    69,   251,     3,
       4,    24,    25,    41,    42,    51,    52,    58,    62,    63,
      65,    67,    71,    72,    76,    77,   101,    42,    51,    52,
      57,    58,    62,    67,    76,   101,    61,   225,   221,   249,
      14,    14,    61,    69,   160,    14,   160,   100,   253,   218,
     213,    61,   242,   253,    14,    13,    61,   218,   218,    13,
     233,   234,   235,   237,    69,   160,    14,   159,   160,   218,
     218,   242,   218,   233,   105,    63,    76,   197,   220,    14,
      14,   218,   220,    26,   252,   249,   248,   249,   248,   249,
      13,   218,   226,   248,   249,   132,   220,    14,    93,   185,
     186,   184,   210,   218,   220,    90,    90,   219,   249,   249,
     219,   219,   221,   219,   221,   249,   219,   221,   219,   219,
     219,   219,   219,   219,   219,   219,   219,   219,   219,   219,
     219,   219,   219,   219,   219,   219,   221,   221,   221,   221,
     221,   221,   221,   223,   219,   218,   218,   217,   161,   162,
     218,   218,    69,   101,   158,   157,   218,    50,    66,    79,
      83,   243,   244,   245,   246,    11,   255,   135,   250,   245,
     174,   248,    13,    14,    13,    14,    14,   218,   158,   154,
      14,    14,   255,    13,    14,   218,   201,   204,   203,   204,
     250,    14,    90,    90,    90,    90,   218,    13,    90,    90,
      90,    13,   217,   185,    14,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    14,    90,     8,    13,
     218,    27,   102,   169,   246,   246,   122,   245,    14,    90,
      28,    46,    94,   241,    90,   218,   218,   234,   218,   220,
     220,   241,   218,    13,   218,   225,   183,   218,   219,   162,
     218,   218,   218,   244,    46,   220,    46,    13,    13,    14,
      14,    13,   185,   186,    90,    95,   170,   220,   220,     5,
      80,    81,   109,   178,    81,   109,   179,   218,   218,   252,
     218,   250,    82,   254
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   129,   130,   130,   131,   131,   131,   131,   132,   132,
     133,   133,   133,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   137,   137,   137,   137,   137,   138,
     139,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   153,   154,   154,   154,
     154,   154,   155,   156,   156,   157,   157,   157,   157,   158,
     158,   159,   159,   160,   161,   161,   162,   162,   162,   163,
     164,   165,   165,   166,   167,   168,   169,   169,   170,   170,
     171,   172,   173,   173,   174,   174,   175,   176,   176,   176,
     177,   177,   178,   178,   178,   178,   179,   179,   180,   181,
     181,   181,   181,   182,   182,   183,   183,   184,   184,   185,
     185,   186,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   197,   198,   199,   199,   200,   200,
     201,   201,   202,   202,   203,   203,   203,   204,   204,   204,
     204,   204,   204,   205,   206,   207,   208,   209,   209,   210,
     210,   211,   211,   212,   212,   213,   213,   214,   214,   215,
     216,   216,   216,   217,   217,   218,   219,   219,   219,   219,
     219,   219,   219,   219,   219,   219,   219,   219,   219,   219,
     219,   219,   219,   219,   219,   219,   219,   219,   219,   219,
     219,   219,   219,   219,   219,   219,   219,   219,   219,   219,
     219,   219,   219,   219,   219,   219,   220,   221,   221,   221,
     222,   222,   223,   223,   223,   223,   223,   223,   223,   223,
     223,   223,   224,   224,   225,   226,   226,   226,   226,   227,
     227,   228,   228,   229,   229,   230,   230,   231,   231,   232,
     232,   232,   233,   233,   234,   234,   235,   236,   236,   236,
     236,   237,   238,   238,   238,   238,   238,   239,   239,   240,
     240,   240,   240,   241,   241,   241,   241,   242,   242,   243,
     243,   244,   244,   244,   244,   244,   245,   245,   246,   246,
     247,   247,   248,   248,   249,   249,   250,   250,   251,   251,
     252,   252,   253,   253,   254,   254,   255,   255
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     3,     2,     2,     1,     1,     0,
       1,     1,     0,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     2,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     3,     4,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     3,     1,     2,     1,     3,
       4,     2,     2,     3,     1,     2,     3,     4,     2,     1,
       1,     1,     0,     3,     3,     1,     1,     3,     3,     3,
       3,     1,     1,     2,     2,     9,     1,     1,     2,     0,
       5,     4,     4,     2,     3,     1,     3,     1,     2,     0,
       7,     7,     1,     1,     1,     3,     1,     1,     2,     1,
       3,     6,     3,     1,     1,     3,     1,     3,     1,     1,
       1,     1,     0,     5,     3,     2,     2,     2,     2,     2,
       2,     2,     3,     1,     1,     2,     1,     1,     3,     1,
       2,     1,     3,     1,     2,     1,     2,     1,     1,     1,
       1,     1,     1,     4,     4,     3,     1,     3,     1,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     4,     4,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     1,     1,     1,     4,     4,     4,     4,
       1,     4,     6,     1,     4,     3,     1,     3,     1,     3,
       1,     0,     1,     2,     4,     4,     1,     2,     1,     4,
       4,     3,     3,     0,     3,     3,     2,     2,     3,     1,
       0,     1,     0,     1,     0,     1,     0,     1,     0,     1,
       1,     0,     3,     1,     1,     1,     1,     1,     1,     4,
       4,     1,     1,     4,     2,     5,     4,     3,     5,     3,
       5,     3,     5,     2,     3,     3,     0,     3,     0,     3,
       1,     1,     2,     2,     2,     2,     1,     4,     1,     1,
       1,     1,     2,     0,     3,     1,     1,     0,     1,     0,
       1,     0,     1,     0,     1,     0,     1,     0
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
#line 237 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				c_line=(yyvsp[-1].cl);
				YYACCEPT;
			}
#line 2019 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 3: /* a_comal_line: error eolnSYM  */
#line 242 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				p_error("Syntax error");
				yyerrok;
				c_line.cmd=0;
				YYACCEPT;
			}
#line 2030 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 4: /* comal_line: intnumSYM program_line optrem  */
#line 251 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl)=(yyvsp[-1].cl);
				(yyval.cl).ld=PARS_ALLOC(struct comal_line_data);
				(yyval.cl).ld->lineno=(yyvsp[-2].num);
				(yyval.cl).ld->rem=(yyvsp[0].str);
				(yyval.cl).lineptr=NULL;
			}
#line 2042 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 5: /* comal_line: complex_stat optrem  */
#line 259 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl)=(yyvsp[-1].cl);
				(yyval.cl).ld=NULL;
				if ((yyvsp[0].str)) {
					(yyval.cl).ld=PARS_ALLOC(struct comal_line_data);
					(yyval.cl).ld->lineno=0;
					(yyval.cl).ld->rem=(yyvsp[0].str);
				}
			}
#line 2056 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 6: /* comal_line: simple_stat optrem  */
#line 269 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl)=(yyvsp[-1].cl);
				(yyval.cl).ld=NULL;
				if ((yyvsp[0].str)) {
					(yyval.cl).ld=PARS_ALLOC(struct comal_line_data);
					(yyval.cl).ld->lineno=0;
					(yyval.cl).ld->rem=(yyvsp[0].str);
				}
			}
#line 2070 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 7: /* comal_line: optrem  */
#line 279 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=0;
			}
#line 2078 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 9: /* optrem: %empty  */
#line 286 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.str)=NULL;
			}
#line 2086 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 12: /* program_line: %empty  */
#line 293 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=0;
			}
#line 2094 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 57: /* simple_stat: xid  */
#line 346 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=execSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 2103 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 60: /* complex_1word: elseSYM  */
#line 355 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=elseSYM;
			}
#line 2111 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 61: /* complex_1word: endcaseSYM  */
#line 359 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=endcaseSYM;
			}
#line 2119 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 62: /* complex_1word: endfuncSYM optid  */
#line 363 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=endfuncSYM;
			}
#line 2127 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 63: /* complex_1word: endifSYM  */
#line 367 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=endifSYM;
			}
#line 2135 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 64: /* complex_1word: loopSYM  */
#line 371 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=loopSYM;
			}
#line 2143 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 65: /* complex_1word: endloopSYM  */
#line 375 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=endloopSYM;
			}
#line 2151 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 66: /* complex_1word: endprocSYM optid2  */
#line 379 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=endprocSYM;
			}
#line 2159 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 67: /* complex_1word: endwhileSYM  */
#line 383 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=endwhileSYM;
			}
#line 2167 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 68: /* complex_1word: endforSYM optnumlvalue  */
#line 387 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=endforSYM;
			}
#line 2175 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 69: /* complex_1word: otherwiseSYM  */
#line 391 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=otherwiseSYM;
			}
#line 2183 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 70: /* complex_1word: repeatSYM  */
#line 395 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=repeatSYM;
				(yyval.cl).lc.ifwhilerec.exp=NULL;
				(yyval.cl).lc.ifwhilerec.stat=NULL;
			}
#line 2193 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 71: /* complex_1word: trapSYM  */
#line 401 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=trapSYM;
				(yyval.cl).lc.traprec.esc=0;
			}
#line 2202 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 72: /* complex_1word: handlerSYM  */
#line 406 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=handlerSYM;
			}
#line 2210 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 73: /* complex_1word: endtrapSYM  */
#line 410 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=endtrapSYM;
			}
#line 2218 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 74: /* simple_1word: nullSYM  */
#line 416 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=nullSYM;
			}
#line 2226 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 75: /* simple_1word: endSYM  */
#line 420 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=endSYM;
			}
#line 2234 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 76: /* simple_1word: exitSYM  */
#line 424 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=exitSYM;
				(yyval.cl).lc.exp=NULL;
			}
#line 2243 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 77: /* simple_1word: pageSYM  */
#line 429 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=pageSYM;
			}
#line 2251 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 78: /* simple_1word: retrySYM  */
#line 433 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=retrySYM;
			}
#line 2259 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 79: /* case_stat: caseSYM exp optof  */
#line 439 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=caseSYM;
				(yyval.cl).lc.exp=(yyvsp[-1].exp);
			}
#line 2268 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 80: /* close_stat: closeSYM  */
#line 446 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=closeSYM;
				(yyval.cl).lc.exproot=NULL;
			}
#line 2277 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 81: /* close_stat: closeSYM optfileS exp_list  */
#line 451 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=closeSYM;
				(yyval.cl).lc.exproot=PARS_REVERSE(struct exp_list, (yyvsp[0].expptr));
			}
#line 2286 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 82: /* cursor_stat: cursorSYM numexp commaSYM numexp  */
#line 458 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=cursorSYM;
				(yyval.cl).lc.twoexp.exp1=(yyvsp[-2].exp);
				(yyval.cl).lc.twoexp.exp2=(yyvsp[0].exp);
			}
#line 2296 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 83: /* chdir_stat: chdirSYM stringexp  */
#line 466 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=chdirSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 2305 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 84: /* rmdir_stat: rmdirSYM stringexp  */
#line 473 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=rmdirSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 2314 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 85: /* mkdir_stat: mkdirSYM stringexp  */
#line 480 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=mkdirSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 2323 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 86: /* data_stat: dataSYM exp_list  */
#line 487 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=dataSYM;
				(yyval.cl).lc.exproot=PARS_REVERSE(struct exp_list, (yyvsp[0].expptr));
			}
#line 2332 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 87: /* draw_stat: drawSYM exp_list  */
#line 494 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
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
#line 2356 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 88: /* tone_stat: toneSYM exp_list  */
#line 516 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                                {
				(yyval.cl).cmd=toneSYM;
				(yyval.cl).lc.exproot=PARS_REVERSE(struct exp_list, (yyvsp[0].expptr));
				/* Expected usage: TONE freq_ms duration_ms or numeric expressions */
			}
#line 2366 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 89: /* play_stat: playSYM exp_list  */
#line 524 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                                {
				(yyval.cl).cmd=playSYM;
				(yyval.cl).lc.exproot=PARS_REVERSE(struct exp_list, (yyvsp[0].expptr));
				/* PLAY takes a parameter list or string — parsed as expression list */
			}
#line 2376 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 90: /* sleep_stat: sleepSYM exp_list  */
#line 532 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
			(yyval.cl).cmd=sleepSYM;
			(yyval.cl).lc.exproot=PARS_REVERSE(struct exp_list, (yyvsp[0].expptr));
			/* SLEEP ms_expr (expression list, but only first is used) */
		}
#line 2386 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 91: /* del_stat: delSYM stringexp  */
#line 540 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=delSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 2395 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 92: /* dir_stat: dirSYM opt_stringexp  */
#line 547 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=dirSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 2404 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 93: /* unit_stat: unitSYM stringexp  */
#line 554 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=unitSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 2413 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 94: /* local_stat: localSYM local_list  */
#line 562 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=localSYM;
				(yyval.cl).lc.dimroot=PARS_REVERSE(struct dim_list, (yyvsp[0].dimptr));
			}
#line 2422 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 95: /* local_list: local_list commaSYM local_item  */
#line 568 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=(yyvsp[0].dimptr);
				(yyval.dimptr)->next=(yyvsp[-2].dimptr);
			}
#line 2431 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 96: /* local_list: local_item  */
#line 573 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=(yyvsp[0].dimptr);
				(yyval.dimptr)->next=NULL;
			}
#line 2440 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 97: /* local_item: numid opt_dim_ensions  */
#line 580 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[-1].id),NULL,(yyvsp[0].dimensionptr));
			}
#line 2448 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 98: /* local_item: stringidSYM  */
#line 584 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[0].id),NULL,NULL);
			}
#line 2456 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 99: /* local_item: stringidSYM ofSYM numexp  */
#line 588 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[-2].id),(yyvsp[0].exp),NULL);
			}
#line 2464 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 100: /* local_item: stringidSYM dim_ensions of numexp  */
#line 592 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[-3].id),(yyvsp[0].exp),(yyvsp[-2].dimensionptr));
			}
#line 2472 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 101: /* local_item: stringidSYM dim_ensions  */
#line 596 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[-1].id),NULL,(yyvsp[0].dimensionptr));
			}
#line 2480 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 102: /* dim_stat: dimSYM dim_list  */
#line 603 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=dimSYM;
				(yyval.cl).lc.dimroot=PARS_REVERSE(struct dim_list, (yyvsp[0].dimptr));
			}
#line 2489 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 103: /* dim_list: dim_list commaSYM dim_item  */
#line 610 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=(yyvsp[0].dimptr);
				(yyval.dimptr)->next=(yyvsp[-2].dimptr);
			}
#line 2498 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 104: /* dim_list: dim_item  */
#line 615 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=(yyvsp[0].dimptr);
				(yyval.dimptr)->next=NULL;
			}
#line 2507 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 105: /* dim_item: numid dim_ensions  */
#line 622 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[-1].id),NULL,(yyvsp[0].dimensionptr));
			}
#line 2515 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 106: /* dim_item: stringidSYM ofSYM numexp  */
#line 626 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[-2].id),(yyvsp[0].exp),NULL);
			}
#line 2523 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 107: /* dim_item: stringidSYM dim_ensions of numexp  */
#line 630 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[-3].id),(yyvsp[0].exp),(yyvsp[-2].dimensionptr));
			}
#line 2531 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 108: /* dim_item: stringidSYM dim_ensions  */
#line 634 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[-1].id),NULL,(yyvsp[0].dimensionptr));
			}
#line 2539 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 112: /* opt_dim_ensions: %empty  */
#line 645 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimensionptr)=NULL;
			}
#line 2547 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 113: /* dim_ensions: lparenSYM dim_ension_list rparenSYM  */
#line 651 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimensionptr)=(yyvsp[-1].dimensionptr);
			}
#line 2555 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 114: /* dim_ension_list: dim_ension_list commaSYM dim_ension  */
#line 657 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimensionptr)=(yyvsp[0].dimensionptr);
				(yyval.dimensionptr)->next=(yyvsp[-2].dimensionptr);
			}
#line 2564 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 115: /* dim_ension_list: dim_ension  */
#line 662 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimensionptr)=(yyvsp[0].dimensionptr);
				(yyval.dimensionptr)->next=NULL;
			}
#line 2573 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 116: /* dim_ension: numexp  */
#line 669 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimensionptr)=PARS_ALLOC(struct dim_ension);
				(yyval.dimensionptr)->bottom=NULL;
				(yyval.dimensionptr)->top=(yyvsp[0].exp);
			}
#line 2583 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 117: /* dim_ension: numexp colonSYM numexp  */
#line 675 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimensionptr)=PARS_ALLOC(struct dim_ension);
				(yyval.dimensionptr)->bottom=(yyvsp[-2].exp);
				(yyval.dimensionptr)->top=(yyvsp[0].exp);
			}
#line 2593 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 118: /* dim_ension: numexp becminusSYM numexp  */
#line 681 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimensionptr)=PARS_ALLOC(struct dim_ension);
				(yyval.dimensionptr)->bottom=(yyvsp[-2].exp);
				(yyval.dimensionptr)->top=pars_exp_unary(minusSYM,(yyvsp[0].exp));
			}
#line 2603 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 119: /* elif_stat: elifSYM numexp optthen  */
#line 689 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=elifSYM;
				(yyval.cl).lc.exp=(yyvsp[-1].exp);
			}
#line 2612 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 120: /* exit_stat: exitSYM ifwhen numexp  */
#line 696 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=exitSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 2621 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 123: /* exec_stat: execSYM xid  */
#line 707 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=execSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 2630 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 124: /* spawn_stat: spawnSYM xid  */
#line 714 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=spawnSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 2639 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 125: /* for_stat: forSYM numlvalue assign1 numexp todownto numexp optstep optdo optsimple_stat  */
#line 721 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=forSYM;
				(yyval.cl).lc.forrec.lval=(yyvsp[-7].exp);
				(yyval.cl).lc.forrec.from=(yyvsp[-5].exp);
				(yyval.cl).lc.forrec.mode=(yyvsp[-4].inum);
				(yyval.cl).lc.forrec.to=(yyvsp[-3].exp);
				(yyval.cl).lc.forrec.step=(yyvsp[-2].exp);
				(yyval.cl).lc.forrec.stat=(yyvsp[0].pcl);
			}
#line 2653 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 126: /* todownto: toSYM  */
#line 733 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=toSYM;
			}
#line 2661 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 127: /* todownto: downtoSYM  */
#line 737 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=downtoSYM;
			}
#line 2669 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 128: /* optstep: stepSYM numexp  */
#line 743 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=(yyvsp[0].exp);
			}
#line 2677 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 129: /* optstep: %empty  */
#line 747 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=NULL;
			}
#line 2685 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 130: /* func_stat: funcSYM id procfunc_head optclosed opt_external  */
#line 753 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=funcSYM;
				(yyval.cl).lc.pfrec.id=(yyvsp[-3].id);
				(yyval.cl).lc.pfrec.parmroot=PARS_REVERSE(struct parm_list, (yyvsp[-2].parmptr));
				(yyval.cl).lc.pfrec.closed=(yyvsp[-1].inum);
				(yyval.cl).lc.pfrec.external=(yyvsp[0].extptr);
			}
#line 2697 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 131: /* if_stat: ifSYM numexp optthen optsimple_stat  */
#line 763 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=ifSYM;
				(yyval.cl).lc.ifwhilerec.exp=(yyvsp[-2].exp);
				(yyval.cl).lc.ifwhilerec.stat=(yyvsp[0].pcl);
			}
#line 2707 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 132: /* import_stat: importSYM id colonSYM import_list  */
#line 771 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=importSYM;
				(yyval.cl).lc.importrec.id=(yyvsp[-2].id);
				(yyval.cl).lc.importrec.importroot=PARS_REVERSE(struct import_list, (yyvsp[0].importptr));
			}
#line 2717 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 133: /* import_stat: importSYM import_list  */
#line 777 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=importSYM;
				(yyval.cl).lc.importrec.id=NULL;
				(yyval.cl).lc.importrec.importroot=PARS_REVERSE(struct import_list, (yyvsp[0].importptr));
			}
#line 2727 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 134: /* import_list: import_list commaSYM oneparm  */
#line 785 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.importptr)=PARS_ALLOC(struct import_list);
				(yyval.importptr)->id=(yyvsp[0].oneparm).id;
				(yyval.importptr)->array=(yyvsp[0].oneparm).array;
				(yyval.importptr)->next=(yyvsp[-2].importptr);				
			}
#line 2738 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 135: /* import_list: oneparm  */
#line 792 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.importptr)=PARS_ALLOC(struct import_list);
				(yyval.importptr)->id=(yyvsp[0].oneparm).id;
				(yyval.importptr)->array=(yyvsp[0].oneparm).array;
				(yyval.importptr)->next=NULL;
			}
#line 2749 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 136: /* input_stat: inputSYM input_modifier lval_list  */
#line 801 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=inputSYM;
				(yyval.cl).lc.inputrec.modifier=(yyvsp[-1].imod);
				(yyval.cl).lc.inputrec.lvalroot=PARS_REVERSE(struct exp_list, (yyvsp[0].expptr));
			}
#line 2759 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 137: /* input_modifier: io_designator  */
#line 809 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.imod)=PARS_ALLOC(struct input_modifier);
				(yyval.imod)->type=fileSYM;
				(yyval.imod)->data.twoexp=(yyvsp[0].twoexp);
			}
#line 2769 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 138: /* input_modifier: stringSYM colonSYM  */
#line 815 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.imod)=PARS_ALLOC(struct input_modifier);
				(yyval.imod)->type=stringSYM;
				(yyval.imod)->data.str=(yyvsp[-1].str);
			}
#line 2779 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 139: /* input_modifier: %empty  */
#line 821 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.imod)=NULL;
			}
#line 2787 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 140: /* open_stat: openSYM fileSYM numexp commaSYM stringexp commaSYM open_type  */
#line 827 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=openSYM;
				(yyval.cl).lc.openrec=(yyvsp[0].openrec);
				(yyval.cl).lc.openrec.filenum=(yyvsp[-4].exp);
				(yyval.cl).lc.openrec.filename=(yyvsp[-2].exp);
			}
#line 2798 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 141: /* open_stat: openSYM queueSYM numexp commaSYM stringexp commaSYM queue_type  */
#line 834 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=openSYM;
				(yyval.cl).lc.openrec=(yyvsp[0].openrec);
				(yyval.cl).lc.openrec.filenum=(yyvsp[-4].exp);
				(yyval.cl).lc.openrec.filename=(yyvsp[-2].exp);
			}
#line 2809 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 142: /* open_type: readSYM  */
#line 843 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.openrec).type=readSYM;
				(yyval.openrec).reclen=NULL;
				(yyval.openrec).read_only=0;
			}
#line 2819 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 143: /* open_type: writeSYM  */
#line 849 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.openrec).type=writeSYM;
				(yyval.openrec).reclen=NULL;
				(yyval.openrec).read_only=0;
			}
#line 2829 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 144: /* open_type: appendSYM  */
#line 855 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.openrec).type=appendSYM;
				(yyval.openrec).reclen=NULL;
				(yyval.openrec).read_only=0;
			}
#line 2839 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 145: /* open_type: randomSYM numexp optread_only  */
#line 861 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.openrec).type=randomSYM;
				(yyval.openrec).reclen=(yyvsp[-1].exp);
				(yyval.openrec).read_only=(yyvsp[0].inum);
			}
#line 2849 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 146: /* queue_type: readSYM  */
#line 869 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.openrec).type=qreadSYM;
				(yyval.openrec).reclen=NULL;
				(yyval.openrec).read_only=0;
			}
#line 2859 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 147: /* queue_type: writeSYM  */
#line 875 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.openrec).type=qwriteSYM;
				(yyval.openrec).reclen=NULL;
				(yyval.openrec).read_only=0;
			}
#line 2869 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 148: /* os_stat: osSYM stringexp  */
#line 883 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=osSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 2878 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 149: /* print_stat: printi  */
#line 890 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=printSYM;
				(yyval.cl).lc.printrec.modifier=NULL;
				(yyval.cl).lc.printrec.printroot=NULL;
				(yyval.cl).lc.printrec.pr_sep=0;
			}
#line 2889 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 150: /* print_stat: printi print_list optpr_sep  */
#line 897 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=printSYM;
				(yyval.cl).lc.printrec.modifier=NULL;
				(yyval.cl).lc.printrec.printroot=PARS_REVERSE(struct print_list, (yyvsp[-1].printptr));
				(yyval.cl).lc.printrec.pr_sep=(yyvsp[0].inum);
			}
#line 2900 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 151: /* print_stat: printi usingSYM stringexp colonSYM prnum_list optpr_sep  */
#line 904 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=printSYM;
				(yyval.cl).lc.printrec.modifier=PARS_ALLOC(struct print_modifier);
				(yyval.cl).lc.printrec.modifier->type=usingSYM;
				(yyval.cl).lc.printrec.modifier->data.str=(yyvsp[-3].exp);
				(yyval.cl).lc.printrec.printroot=PARS_REVERSE(struct print_list, (yyvsp[-1].printptr));
				(yyval.cl).lc.printrec.pr_sep=(yyvsp[0].inum);
			}
#line 2913 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 152: /* print_stat: printi io_designator print_list  */
#line 913 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=printSYM;
				(yyval.cl).lc.printrec.modifier=PARS_ALLOC(struct print_modifier);
				(yyval.cl).lc.printrec.modifier->type=fileSYM;
				(yyval.cl).lc.printrec.modifier->data.twoexp=(yyvsp[-1].twoexp);
				(yyval.cl).lc.printrec.printroot=PARS_REVERSE(struct print_list, (yyvsp[0].printptr));
				(yyval.cl).lc.printrec.pr_sep=0;
			}
#line 2926 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 155: /* prnum_list: prnum_list pr_sep numexp  */
#line 928 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.printptr)=pars_printlist_item((yyvsp[-1].inum),(yyvsp[0].exp),(yyvsp[-2].printptr));
			}
#line 2934 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 156: /* prnum_list: numexp  */
#line 932 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.printptr)=pars_printlist_item(0,(yyvsp[0].exp),NULL);
			}
#line 2942 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 157: /* print_list: print_list pr_sep exp  */
#line 938 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.printptr)=pars_printlist_item((yyvsp[-1].inum),(yyvsp[0].exp),(yyvsp[-2].printptr));
			}
#line 2950 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 158: /* print_list: exp  */
#line 942 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.printptr)=pars_printlist_item(0,(yyvsp[0].exp),NULL);
			}
#line 2958 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 159: /* pr_sep: commaSYM  */
#line 948 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=commaSYM;
			}
#line 2966 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 160: /* pr_sep: semicolonSYM  */
#line 952 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=semicolonSYM;
			}
#line 2974 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 162: /* optpr_sep: %empty  */
#line 959 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=0;
			}
#line 2982 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 163: /* proc_stat: procSYM idSYM procfunc_head optclosed opt_external  */
#line 965 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=procSYM;
				(yyval.cl).lc.pfrec.id=(yyvsp[-3].id);
				(yyval.cl).lc.pfrec.parmroot=PARS_REVERSE(struct parm_list, (yyvsp[-2].parmptr));
				(yyval.cl).lc.pfrec.closed=(yyvsp[-1].inum);
				(yyval.cl).lc.pfrec.external=(yyvsp[0].extptr);
			}
#line 2994 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 164: /* read_stat: readSYM optfile lval_list  */
#line 975 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=readSYM;
				(yyval.cl).lc.readrec.modifier=(yyvsp[-1].twoexpp);
				(yyval.cl).lc.readrec.lvalroot=PARS_REVERSE(struct exp_list, (yyvsp[0].expptr));
			}
#line 3004 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 165: /* restore_stat: restoreSYM optid2  */
#line 983 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=restoreSYM;
				(yyval.cl).lc.id=(yyvsp[0].id);
			}
#line 3013 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 166: /* return_stat: returnSYM optexp  */
#line 990 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=returnSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 3022 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 167: /* select_out_stat: select_outputSYM stringexp  */
#line 997 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=select_outputSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 3031 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 168: /* select_in_stat: select_inputSYM stringexp  */
#line 1005 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=select_inputSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 3040 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 169: /* stop_stat: stopSYM optexp  */
#line 1012 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=stopSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 3049 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 170: /* sys_stat: sysSYM exp_list  */
#line 1019 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=sysSYM;
				(yyval.cl).lc.exproot=PARS_REVERSE(struct exp_list, (yyvsp[0].expptr));
			}
#line 3058 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 171: /* until_stat: untilSYM numexp  */
#line 1026 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=untilSYM;
				(yyval.cl).lc.exp=(yyvsp[0].exp);
			}
#line 3067 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 172: /* trap_stat: trapSYM escSYM plusorminus  */
#line 1033 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=trapSYM;
				(yyval.cl).lc.traprec.esc=(yyvsp[0].inum);
			}
#line 3076 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 173: /* plusorminus: plusSYM  */
#line 1040 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=plusSYM;
			}
#line 3084 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 174: /* plusorminus: minusSYM  */
#line 1044 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=minusSYM;
			}
#line 3092 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 175: /* when_stat: whenSYM when_list  */
#line 1050 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=whenSYM;
				(yyval.cl).lc.whenroot=PARS_REVERSE(struct when_list, (yyvsp[0].whenptr));
			}
#line 3101 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 178: /* when_numlist: when_numlist commaSYM when_numitem  */
#line 1061 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.whenptr)=(yyvsp[0].whenptr);
				(yyval.whenptr)->next=(yyvsp[-2].whenptr);
			}
#line 3110 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 180: /* when_numitem: relop numexp  */
#line 1069 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.whenptr)=pars_whenlist_item((yyvsp[-1].inum),(yyvsp[0].exp),NULL);
			}
#line 3118 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 181: /* when_numitem: numexp  */
#line 1073 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.whenptr)=pars_whenlist_item(eqlSYM,(yyvsp[0].exp),NULL);
			}
#line 3126 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 182: /* when_strlist: when_strlist commaSYM when_stritem  */
#line 1079 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.whenptr)=(yyvsp[0].whenptr);
				(yyval.whenptr)->next=(yyvsp[-2].whenptr);
			}
#line 3135 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 184: /* when_stritem: relop stringexp  */
#line 1087 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.whenptr)=pars_whenlist_item((yyvsp[-1].inum),(yyvsp[0].exp),NULL);
			}
#line 3143 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 185: /* when_stritem: stringexp  */
#line 1091 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.whenptr)=pars_whenlist_item(eqlSYM,(yyvsp[0].exp),NULL);
			}
#line 3151 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 186: /* when_stritem: inSYM stringexp  */
#line 1095 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.whenptr)=pars_whenlist_item(inSYM,(yyvsp[0].exp),NULL);
			}
#line 3159 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 187: /* relop: gtrSYM  */
#line 1101 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=gtrSYM;
			}
#line 3167 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 188: /* relop: lssSYM  */
#line 1105 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=lssSYM;
			}
#line 3175 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 189: /* relop: eqlSYM  */
#line 1109 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=eqlSYM;
			}
#line 3183 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 190: /* relop: neqSYM  */
#line 1113 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=neqSYM;
			}
#line 3191 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 191: /* relop: geqSYM  */
#line 1117 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=geqSYM;
			}
#line 3199 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 192: /* relop: leqSYM  */
#line 1121 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=leqSYM;
			}
#line 3207 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 193: /* while_stat: whileSYM numexp optdo optsimple_stat  */
#line 1127 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=whileSYM;
				(yyval.cl).lc.ifwhilerec.exp=(yyvsp[-2].exp);
				(yyval.cl).lc.ifwhilerec.stat=(yyvsp[0].pcl);
			}
#line 3217 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 194: /* repeat_stat: repeatSYM simple_stat untilSYM numexp  */
#line 1135 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=repeatSYM;
				(yyval.cl).lc.ifwhilerec.exp=(yyvsp[0].exp);
				(yyval.cl).lc.ifwhilerec.stat=stat_dup(&(yyvsp[-2].cl));
			}
#line 3227 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 195: /* write_stat: writeSYM file_designator exp_list  */
#line 1143 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=writeSYM;
				(yyval.cl).lc.writerec.twoexp=(yyvsp[-1].twoexp);
				(yyval.cl).lc.writerec.exproot=PARS_REVERSE(struct exp_list, (yyvsp[0].expptr));
			}
#line 3237 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 196: /* assign_stat: assign_list  */
#line 1151 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=becomesSYM;
				(yyval.cl).lc.assignroot=PARS_REVERSE(struct assign_list, (yyvsp[0].assignptr));
			}
#line 3246 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 197: /* assign_list: assign_list semicolonSYM assign_item  */
#line 1158 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.assignptr)=(yyvsp[0].assignptr);
				(yyval.assignptr)->next=(yyvsp[-2].assignptr);
			}
#line 3255 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 198: /* assign_list: assign_item  */
#line 1163 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.assignptr)->next=NULL;
			}
#line 3263 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 199: /* assign_item: numlvalue nassign numexp  */
#line 1169 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.assignptr)=pars_assign_item((yyvsp[-1].inum),(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3271 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 200: /* assign_item: strlvalue sassign stringexp  */
#line 1173 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.assignptr)=pars_assign_item((yyvsp[-1].inum),(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3279 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 204: /* sassign: becplusSYM  */
#line 1184 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=becplusSYM;
			}
#line 3287 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 205: /* assign1: eqlSYM  */
#line 1190 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=becomesSYM;
			}
#line 3295 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 206: /* assign1: becomesSYM  */
#line 1194 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=becomesSYM;
			}
#line 3303 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 207: /* assign2: becplusSYM  */
#line 1200 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=becplusSYM;
			}
#line 3311 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 208: /* assign2: becminusSYM  */
#line 1204 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=becminusSYM;
			}
#line 3319 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 209: /* label_stat: idSYM colonSYM  */
#line 1210 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.cl).cmd=idSYM;
				(yyval.cl).lc.id=(yyvsp[-1].id);
			}
#line 3328 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 210: /* xid: idSYM  */
#line 1217 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_id(idSYM,(yyvsp[0].id),NULL);
			}
#line 3336 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 211: /* xid: idSYM lparenSYM exp_list rparenSYM  */
#line 1221 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_id(idSYM,(yyvsp[-3].id),(yyvsp[-1].expptr));
			}
#line 3344 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 212: /* xid: idSYM lparenSYM opt_commalist rparenSYM  */
#line 1225 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_array(idSYM,(yyvsp[-3].id),T_ARRAY);
			}
#line 3352 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 215: /* numexp: numexp2  */
#line 1235 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_num((yyvsp[0].exp));
			}
#line 3360 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 216: /* numexp2: numexp2 eqlSYM numexp2  */
#line 1241 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(eqlSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3368 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 217: /* numexp2: numexp2 neqSYM numexp2  */
#line 1245 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(neqSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3376 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 218: /* numexp2: numexp2 lssSYM numexp2  */
#line 1249 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(lssSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3384 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 219: /* numexp2: numexp2 gtrSYM numexp2  */
#line 1253 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(gtrSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3392 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 220: /* numexp2: numexp2 leqSYM numexp2  */
#line 1257 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(leqSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3400 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 221: /* numexp2: numexp2 geqSYM numexp2  */
#line 1261 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(geqSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3408 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 222: /* numexp2: numexp2 andSYM numexp2  */
#line 1265 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(andSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3416 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 223: /* numexp2: numexp2 andthenSYM numexp2  */
#line 1269 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(andthenSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3424 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 224: /* numexp2: numexp2 orSYM numexp2  */
#line 1273 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(orSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3432 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 225: /* numexp2: numexp2 orthenSYM numexp2  */
#line 1277 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(orthenSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3440 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 226: /* numexp2: numexp2 eorSYM numexp2  */
#line 1281 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(eorSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3448 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 227: /* numexp2: numexp2 plusSYM numexp2  */
#line 1285 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(plusSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3456 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 228: /* numexp2: numexp2 minusSYM numexp2  */
#line 1289 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(minusSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3464 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 229: /* numexp2: numexp2 timesSYM numexp2  */
#line 1293 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(timesSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3472 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 230: /* numexp2: numexp2 divideSYM numexp2  */
#line 1297 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(divideSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3480 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 231: /* numexp2: numexp2 powerSYM numexp2  */
#line 1301 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(powerSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3488 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 232: /* numexp2: numexp2 divSYM numexp2  */
#line 1305 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(divSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3496 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 233: /* numexp2: numexp2 modSYM numexp2  */
#line 1309 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(modSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3504 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 234: /* numexp2: stringexp2 eqlSYM stringexp2  */
#line 1313 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(eqlSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3512 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 235: /* numexp2: stringexp2 neqSYM stringexp2  */
#line 1317 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(neqSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3520 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 236: /* numexp2: stringexp2 lssSYM stringexp2  */
#line 1321 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(lssSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3528 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 237: /* numexp2: stringexp2 gtrSYM stringexp2  */
#line 1325 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(gtrSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3536 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 238: /* numexp2: stringexp2 leqSYM stringexp2  */
#line 1329 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(leqSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3544 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 239: /* numexp2: stringexp2 geqSYM stringexp2  */
#line 1333 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(geqSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3552 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 240: /* numexp2: stringexp2 inSYM stringexp2  */
#line 1337 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(inSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3560 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 241: /* numexp2: minusSYM numexp2  */
#line 1341 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary(minusSYM,(yyvsp[0].exp));
			}
#line 3568 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 242: /* numexp2: plusSYM numexp2  */
#line 1345 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary(plusSYM,(yyvsp[0].exp));
			}
#line 3576 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 243: /* numexp2: intnumSYM  */
#line 1349 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_int((yyvsp[0].num));
			}
#line 3584 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 244: /* numexp2: floatnumSYM  */
#line 1353 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_float(&(yyvsp[0].dubbel));
			}
#line 3592 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 246: /* numexp2: tsrnSYM lparenSYM stringexp2 rparenSYM  */
#line 1358 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary((yyvsp[-3].inum),(yyvsp[-1].exp));
			}
#line 3600 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 247: /* numexp2: lenSYM lparenSYM stringexp2 rparenSYM  */
#line 1362 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary((yyvsp[-3].inum),(yyvsp[-1].exp));
			}
#line 3608 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 248: /* numexp2: lenSYM lparenSYM numexp2 rparenSYM  */
#line 1366 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary((yyvsp[-3].inum),(yyvsp[-1].exp));
			}
#line 3616 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 249: /* numexp2: tnrnSYM lparenSYM numexp2 rparenSYM  */
#line 1370 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary((yyvsp[-3].inum),(yyvsp[-1].exp));
			}
#line 3624 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 250: /* numexp2: rndSYM  */
#line 1374 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(_RND,NULL,NULL);
			}
#line 3632 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 251: /* numexp2: rndSYM lparenSYM numexp2 rparenSYM  */
#line 1378 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(_RND,NULL,(yyvsp[-1].exp));
			}
#line 3640 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 252: /* numexp2: rndSYM lparenSYM numexp2 commaSYM numexp2 rparenSYM  */
#line 1382 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(_RND,(yyvsp[-3].exp),(yyvsp[-1].exp));
			}
#line 3648 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 253: /* numexp2: rnSYM  */
#line 1386 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_const((yyvsp[0].inum));
			}
#line 3656 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 254: /* numexp2: sysSYM lparenSYM exp_list rparenSYM  */
#line 1390 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_sys(sysSYM,T_SYS,(yyvsp[-1].expptr));
			}
#line 3664 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 255: /* numexp2: lparenSYM numexp2 rparenSYM  */
#line 1394 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary(lparenSYM,(yyvsp[-1].exp));
			}
#line 3672 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 256: /* stringexp: stringexp2  */
#line 1400 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_str((yyvsp[0].exp));
			}
#line 3680 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 257: /* stringexp2: stringexp2 plusSYM string_factor  */
#line 1406 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(plusSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3688 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 259: /* stringexp2: stringexp2 timesSYM numexp2  */
#line 1411 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(timesSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3696 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 261: /* opt_stringexp: %empty  */
#line 1418 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=NULL;
			}
#line 3704 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 263: /* string_factor: string_factor substr_spec  */
#line 1425 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_substr((yyvsp[-1].exp),&(yyvsp[0].twoexp));
			}
#line 3712 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 264: /* string_factor: tnrsSYM lparenSYM numexp2 rparenSYM  */
#line 1429 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary((yyvsp[-3].inum),(yyvsp[-1].exp));
			}
#line 3720 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 265: /* string_factor: tsrsSYM lparenSYM stringexp2 rparenSYM  */
#line 1433 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary((yyvsp[-3].inum),(yyvsp[-1].exp));
			}
#line 3728 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 266: /* string_factor: rsSYM  */
#line 1437 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_const((yyvsp[0].inum));
			}
#line 3736 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 267: /* string_factor: tonrsSYM opt_arg  */
#line 1441 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary((yyvsp[-1].inum),(yyvsp[0].exp));
			}
#line 3744 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 268: /* string_factor: stringSYM  */
#line 1445 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_string((yyvsp[0].str));
			}
#line 3752 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 269: /* string_factor: syssSYM lparenSYM exp_list rparenSYM  */
#line 1449 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_sys(syssSYM,T_SYSS,(yyvsp[-1].expptr));
			}
#line 3760 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 270: /* string_factor: tsrsnSYM lparenSYM exp_list rparenSYM  */
#line 1453 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
			(yyval.exp)=pars_exp_sys((yyvsp[-3].inum),T_SYSS,(yyvsp[-1].expptr));
			}
#line 3768 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 271: /* string_factor: lparenSYM stringexp2 rparenSYM  */
#line 1457 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary(lparenSYM,(yyvsp[-1].exp));
			}
#line 3776 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 272: /* opt_arg: lparenSYM numexp2 rparenSYM  */
#line 1463 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=(yyvsp[-1].exp);
			}
#line 3784 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 273: /* opt_arg: %empty  */
#line 1467 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=NULL;
			}
#line 3792 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 274: /* substr_spec: lparenSYM substr_spec2 rparenSYM  */
#line 1473 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp)=(yyvsp[-1].twoexp);
			}
#line 3800 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 275: /* substr_spec2: numexp colonSYM numexp  */
#line 1479 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp).exp1=(yyvsp[-2].exp);
				(yyval.twoexp).exp2=(yyvsp[0].exp);
			}
#line 3809 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 276: /* substr_spec2: colonSYM numexp  */
#line 1484 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp).exp1=NULL;
				(yyval.twoexp).exp2=(yyvsp[0].exp);
			}
#line 3818 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 277: /* substr_spec2: numexp colonSYM  */
#line 1489 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp).exp1=(yyvsp[-1].exp);
				(yyval.twoexp).exp2=NULL;
			}
#line 3827 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 278: /* substr_spec2: colonSYM numexp colonSYM  */
#line 1494 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp).exp1=(yyvsp[-1].exp);
				(yyval.twoexp).exp2=(yyvsp[-1].exp);
			}
#line 3836 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 280: /* optnumlvalue: %empty  */
#line 1502 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=NULL;
			}
#line 3844 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 282: /* optexp: %empty  */
#line 1509 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=NULL;
			}
#line 3852 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 284: /* optid: %empty  */
#line 1516 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.id)=NULL;
			}
#line 3860 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 286: /* optid2: %empty  */
#line 1523 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.id)=NULL;
			}
#line 3868 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 287: /* optfile: file_designator  */
#line 1529 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexpp)=PARS_ALLOC(struct two_exp);
				
				*((yyval.twoexpp))=(yyvsp[0].twoexp);
			}
#line 3878 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 288: /* optfile: %empty  */
#line 1535 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {	
				(yyval.twoexpp)=NULL;
			}
#line 3886 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 292: /* lval_list: lval_list commaSYM lvalue  */
#line 1546 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.expptr)=pars_explist_item((yyvsp[0].exp),(yyvsp[-2].expptr));
			}
#line 3894 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 293: /* lval_list: lvalue  */
#line 1550 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.expptr)=pars_explist_item((yyvsp[0].exp),NULL);
			}
#line 3902 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 296: /* numlvalue: numlvalue2  */
#line 1560 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				if (!exp_list_of_nums((yyvsp[0].exp)->e.expid.exproot))
					pars_error("Indices of numeric lvalue \"%s\" must be numerics",(yyvsp[0].exp)->e.expid.id->name);
			}
#line 3911 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 298: /* numlvalue2: intidSYM  */
#line 1568 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_id(intidSYM,(yyvsp[0].id),NULL);
			}
#line 3919 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 299: /* numlvalue2: intidSYM lparenSYM exp_list rparenSYM  */
#line 1572 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_id(intidSYM,(yyvsp[-3].id),(yyvsp[-1].expptr));
			}
#line 3927 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 300: /* numlvalue2: intidSYM lparenSYM opt_commalist rparenSYM  */
#line 1576 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_array(intidSYM,(yyvsp[-3].id),T_ARRAY);
			}
#line 3935 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 301: /* strlvalue: strlvalue2  */
#line 1582 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				if (!exp_list_of_nums((yyvsp[0].exp)->e.expsid.exproot))
					pars_error("Indices of string lvalue \"%s\" must be numerics",(yyvsp[0].exp)->e.expsid.id->name);
			}
#line 3944 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 302: /* strlvalue2: stringidSYM  */
#line 1589 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_sid((yyvsp[0].id),NULL,NULL);
			}
#line 3952 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 303: /* strlvalue2: stringidSYM lparenSYM exp_list rparenSYM  */
#line 1593 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_sid((yyvsp[-3].id),(yyvsp[-1].expptr),NULL);
			}
#line 3960 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 304: /* strlvalue2: stringidSYM substr_spec  */
#line 1597 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_sid((yyvsp[-1].id),NULL,&(yyvsp[0].twoexp));
			}
#line 3968 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 305: /* strlvalue2: stringidSYM lparenSYM exp_list rparenSYM substr_spec  */
#line 1601 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_sid((yyvsp[-4].id),(yyvsp[-2].expptr),&(yyvsp[0].twoexp));
			}
#line 3976 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 306: /* strlvalue2: stringidSYM lparenSYM opt_commalist rparenSYM  */
#line 1605 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_array(intidSYM,(yyvsp[-3].id),T_SARRAY);
			}
#line 3984 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 307: /* file_designator: fileSYM numexp colonSYM  */
#line 1611 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp).exp1=(yyvsp[-1].exp);
				(yyval.twoexp).exp2=NULL;
			}
#line 3993 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 308: /* file_designator: fileSYM numexp commaSYM numexp colonSYM  */
#line 1616 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp).exp1=(yyvsp[-3].exp);
				(yyval.twoexp).exp2=(yyvsp[-1].exp);
			}
#line 4002 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 309: /* io_designator: fileSYM numexp colonSYM  */
#line 1623 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp).exp1=(yyvsp[-1].exp);
				(yyval.twoexp).exp2=NULL;
			}
#line 4011 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 310: /* io_designator: fileSYM numexp commaSYM numexp colonSYM  */
#line 1628 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp).exp1=(yyvsp[-3].exp);
				(yyval.twoexp).exp2=(yyvsp[-1].exp);
			}
#line 4020 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 311: /* io_designator: queueSYM numexp colonSYM  */
#line 1633 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp).exp1=(yyvsp[-1].exp);
				(yyval.twoexp).exp2=NULL;
			}
#line 4029 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 312: /* io_designator: queueSYM numexp commaSYM numexp colonSYM  */
#line 1638 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp).exp1=(yyvsp[-3].exp);
				(yyval.twoexp).exp2=(yyvsp[-1].exp);
			}
#line 4038 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 313: /* opt_external: externalSYM stringexp  */
#line 1645 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.extptr)=PARS_ALLOC(struct ext_rec);
				
				(yyval.extptr)->dynamic=0;
				(yyval.extptr)->filename=(yyvsp[0].exp);
				(yyval.extptr)->seg=NULL;
			}
#line 4050 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 314: /* opt_external: dynamicSYM externalSYM stringexp  */
#line 1653 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.extptr)=PARS_ALLOC(struct ext_rec);
				
				(yyval.extptr)->dynamic=dynamicSYM;
				(yyval.extptr)->filename=(yyvsp[0].exp);
				(yyval.extptr)->seg=NULL;
			}
#line 4062 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 315: /* opt_external: staticSYM externalSYM stringexp  */
#line 1661 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.extptr)=PARS_ALLOC(struct ext_rec);
				
				(yyval.extptr)->dynamic=staticSYM;
				(yyval.extptr)->filename=(yyvsp[0].exp);
				(yyval.extptr)->seg=NULL;
			}
#line 4074 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 316: /* opt_external: %empty  */
#line 1669 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.extptr)=NULL;
			}
#line 4082 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 317: /* procfunc_head: lparenSYM parmlist rparenSYM  */
#line 1675 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=(yyvsp[-1].parmptr);
			}
#line 4090 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 318: /* procfunc_head: %empty  */
#line 1679 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=NULL;
			}
#line 4098 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 319: /* parmlist: parmlist commaSYM parmitem  */
#line 1685 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=(yyvsp[0].parmptr);
				(yyval.parmptr)->next=(yyvsp[-2].parmptr);
			}
#line 4107 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 320: /* parmlist: parmitem  */
#line 1690 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=(yyvsp[0].parmptr);
				(yyval.parmptr)->next=NULL;
			}
#line 4116 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 321: /* parmitem: oneparm  */
#line 1697 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=PARS_ALLOC(struct parm_list);
				(yyval.parmptr)->id=(yyvsp[0].oneparm).id;
				(yyval.parmptr)->array=(yyvsp[0].oneparm).array;
				(yyval.parmptr)->ref=0;
			}
#line 4127 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 322: /* parmitem: refSYM oneparm  */
#line 1704 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=PARS_ALLOC(struct parm_list);
				(yyval.parmptr)->id=(yyvsp[0].oneparm).id;
				(yyval.parmptr)->array=(yyvsp[0].oneparm).array;
				(yyval.parmptr)->ref=refSYM;
			}
#line 4138 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 323: /* parmitem: nameSYM id  */
#line 1711 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=PARS_ALLOC(struct parm_list);
				(yyval.parmptr)->id=(yyvsp[0].id);
				(yyval.parmptr)->array=0;
				(yyval.parmptr)->ref=nameSYM;
			}
#line 4149 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 324: /* parmitem: procSYM idSYM  */
#line 1718 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=PARS_ALLOC(struct parm_list);
				(yyval.parmptr)->id=(yyvsp[0].id);
				(yyval.parmptr)->array=0;
				(yyval.parmptr)->ref=procSYM;
			}
#line 4160 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 325: /* parmitem: funcSYM id  */
#line 1725 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=PARS_ALLOC(struct parm_list);
				(yyval.parmptr)->id=(yyvsp[0].id);
				(yyval.parmptr)->array=0;
				(yyval.parmptr)->ref=funcSYM;
			}
#line 4171 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 326: /* oneparm: id  */
#line 1734 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.oneparm).id=(yyvsp[0].id);
				(yyval.oneparm).array=0;
			}
#line 4180 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 327: /* oneparm: id lparenSYM opt_commalist rparenSYM  */
#line 1739 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.oneparm).id=(yyvsp[-3].id);
				(yyval.oneparm).array=1;
			}
#line 4189 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 334: /* exp_list: exp_list commaSYM exp  */
#line 1758 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.expptr)=pars_explist_item((yyvsp[0].exp),(yyvsp[-2].expptr));
				}
#line 4197 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 335: /* exp_list: exp  */
#line 1762 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.expptr)=pars_explist_item((yyvsp[0].exp),NULL);
			}
#line 4205 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 336: /* optsimple_stat: simple_stat  */
#line 1768 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				if ((yyvsp[0].cl).cmd<0)
					(yyval.pcl)=NULL;
				else
				{
					(yyval.pcl)=stat_dup(&(yyvsp[0].cl));
					(yyval.pcl)->ld=NULL;
				}
			}
#line 4219 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 337: /* optsimple_stat: %empty  */
#line 1778 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl)=NULL;
			}
#line 4227 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 344: /* optread_only: read_onlySYM  */
#line 1796 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=read_onlySYM;
			}
#line 4235 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 345: /* optread_only: %empty  */
#line 1800 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=0;
			}
#line 4243 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 346: /* optclosed: closedSYM  */
#line 1806 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=closedSYM;
			}
#line 4251 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;

  case 347: /* optclosed: %empty  */
#line 1810 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=0;
			}
#line 4259 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"
    break;


#line 4263 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.cc"

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

#line 1815 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"


PRIVATE void p_error(const char *s)
	{
		pars_error((char *)s);
		yyclearin;
	}
	
