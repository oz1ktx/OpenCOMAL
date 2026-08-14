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
#include "comal_ast_modern.h"
#include "modern_builders.h"
#include "ast_compat.h"

#include <string.h>

#define yyunion(x,y)	( (*(x)) = (*(y)) )

PUBLIC struct comal_line c_line;
PUBLIC comal::ComalLine* c_line_modern = nullptr;

PRIVATE void p_error(const char *msg);

extern int yylex();
extern int exp_list_of_nums(struct exp_list *root);
extern char *exp_cmd(struct expression *exp);
extern struct comal_line *stat_dup(struct comal_line *stat);

#define PARS_ALLOC(type) static_cast<type *>(mem_alloc(PARSE_POOL, sizeof(type)))
#define PARS_REVERSE(type, root) static_cast<type *>(my_reverse(root))


#line 117 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"

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
  YYSYMBOL_waitSYM = 98,                   /* waitSYM  */
  YYSYMBOL_sysSYM = 99,                    /* sysSYM  */
  YYSYMBOL_syssSYM = 100,                  /* syssSYM  */
  YYSYMBOL_thenSYM = 101,                  /* thenSYM  */
  YYSYMBOL_timesSYM = 102,                 /* timesSYM  */
  YYSYMBOL_toSYM = 103,                    /* toSYM  */
  YYSYMBOL_trapSYM = 104,                  /* trapSYM  */
  YYSYMBOL_unitSYM = 105,                  /* unitSYM  */
  YYSYMBOL_untilSYM = 106,                 /* untilSYM  */
  YYSYMBOL_usingSYM = 107,                 /* usingSYM  */
  YYSYMBOL_whenSYM = 108,                  /* whenSYM  */
  YYSYMBOL_whileSYM = 109,                 /* whileSYM  */
  YYSYMBOL_writeSYM = 110,                 /* writeSYM  */
  YYSYMBOL_qreadSYM = 111,                 /* qreadSYM  */
  YYSYMBOL_qwriteSYM = 112,                /* qwriteSYM  */
  YYSYMBOL_rnSYM = 113,                    /* rnSYM  */
  YYSYMBOL_rsSYM = 114,                    /* rsSYM  */
  YYSYMBOL_tnrnSYM = 115,                  /* tnrnSYM  */
  YYSYMBOL_tnrsSYM = 116,                  /* tnrsSYM  */
  YYSYMBOL_tsrnSYM = 117,                  /* tsrnSYM  */
  YYSYMBOL_tonrsSYM = 118,                 /* tonrsSYM  */
  YYSYMBOL_tsrsSYM = 119,                  /* tsrsSYM  */
  YYSYMBOL_tsrsnSYM = 120,                 /* tsrsnSYM  */
  YYSYMBOL_lenSYM = 121,                   /* lenSYM  */
  YYSYMBOL_floatnumSYM = 122,              /* floatnumSYM  */
  YYSYMBOL_idSYM = 123,                    /* idSYM  */
  YYSYMBOL_intidSYM = 124,                 /* intidSYM  */
  YYSYMBOL_stringidSYM = 125,              /* stringidSYM  */
  YYSYMBOL_intnumSYM = 126,                /* intnumSYM  */
  YYSYMBOL_remSYM = 127,                   /* remSYM  */
  YYSYMBOL_stringSYM = 128,                /* stringSYM  */
  YYSYMBOL_USIGN = 129,                    /* USIGN  */
  YYSYMBOL_YYACCEPT = 130,                 /* $accept  */
  YYSYMBOL_a_comal_line = 131,             /* a_comal_line  */
  YYSYMBOL_comal_line = 132,               /* comal_line  */
  YYSYMBOL_optrem = 133,                   /* optrem  */
  YYSYMBOL_program_line = 134,             /* program_line  */
  YYSYMBOL_complex_stat = 135,             /* complex_stat  */
  YYSYMBOL_simple_stat = 136,              /* simple_stat  */
  YYSYMBOL_complex_1word = 137,            /* complex_1word  */
  YYSYMBOL_simple_1word = 138,             /* simple_1word  */
  YYSYMBOL_case_stat = 139,                /* case_stat  */
  YYSYMBOL_close_stat = 140,               /* close_stat  */
  YYSYMBOL_cursor_stat = 141,              /* cursor_stat  */
  YYSYMBOL_chdir_stat = 142,               /* chdir_stat  */
  YYSYMBOL_rmdir_stat = 143,               /* rmdir_stat  */
  YYSYMBOL_mkdir_stat = 144,               /* mkdir_stat  */
  YYSYMBOL_data_stat = 145,                /* data_stat  */
  YYSYMBOL_draw_stat = 146,                /* draw_stat  */
  YYSYMBOL_tone_stat = 147,                /* tone_stat  */
  YYSYMBOL_play_stat = 148,                /* play_stat  */
  YYSYMBOL_sleep_stat = 149,               /* sleep_stat  */
  YYSYMBOL_del_stat = 150,                 /* del_stat  */
  YYSYMBOL_dir_stat = 151,                 /* dir_stat  */
  YYSYMBOL_unit_stat = 152,                /* unit_stat  */
  YYSYMBOL_local_stat = 153,               /* local_stat  */
  YYSYMBOL_local_list = 154,               /* local_list  */
  YYSYMBOL_local_item = 155,               /* local_item  */
  YYSYMBOL_dim_stat = 156,                 /* dim_stat  */
  YYSYMBOL_dim_list = 157,                 /* dim_list  */
  YYSYMBOL_dim_item = 158,                 /* dim_item  */
  YYSYMBOL_of = 159,                       /* of  */
  YYSYMBOL_opt_dim_ensions = 160,          /* opt_dim_ensions  */
  YYSYMBOL_dim_ensions = 161,              /* dim_ensions  */
  YYSYMBOL_dim_ension_list = 162,          /* dim_ension_list  */
  YYSYMBOL_dim_ension = 163,               /* dim_ension  */
  YYSYMBOL_elif_stat = 164,                /* elif_stat  */
  YYSYMBOL_exit_stat = 165,                /* exit_stat  */
  YYSYMBOL_ifwhen = 166,                   /* ifwhen  */
  YYSYMBOL_exec_stat = 167,                /* exec_stat  */
  YYSYMBOL_spawn_stat = 168,               /* spawn_stat  */
  YYSYMBOL_wait_stat = 169,                /* wait_stat  */
  YYSYMBOL_for_stat = 170,                 /* for_stat  */
  YYSYMBOL_todownto = 171,                 /* todownto  */
  YYSYMBOL_optstep = 172,                  /* optstep  */
  YYSYMBOL_func_stat = 173,                /* func_stat  */
  YYSYMBOL_if_stat = 174,                  /* if_stat  */
  YYSYMBOL_import_stat = 175,              /* import_stat  */
  YYSYMBOL_import_list = 176,              /* import_list  */
  YYSYMBOL_input_stat = 177,               /* input_stat  */
  YYSYMBOL_input_modifier = 178,           /* input_modifier  */
  YYSYMBOL_open_stat = 179,                /* open_stat  */
  YYSYMBOL_open_type = 180,                /* open_type  */
  YYSYMBOL_queue_type = 181,               /* queue_type  */
  YYSYMBOL_os_stat = 182,                  /* os_stat  */
  YYSYMBOL_print_stat = 183,               /* print_stat  */
  YYSYMBOL_printi = 184,                   /* printi  */
  YYSYMBOL_prnum_list = 185,               /* prnum_list  */
  YYSYMBOL_print_list = 186,               /* print_list  */
  YYSYMBOL_pr_sep = 187,                   /* pr_sep  */
  YYSYMBOL_optpr_sep = 188,                /* optpr_sep  */
  YYSYMBOL_proc_stat = 189,                /* proc_stat  */
  YYSYMBOL_read_stat = 190,                /* read_stat  */
  YYSYMBOL_restore_stat = 191,             /* restore_stat  */
  YYSYMBOL_return_stat = 192,              /* return_stat  */
  YYSYMBOL_select_out_stat = 193,          /* select_out_stat  */
  YYSYMBOL_select_in_stat = 194,           /* select_in_stat  */
  YYSYMBOL_stop_stat = 195,                /* stop_stat  */
  YYSYMBOL_sys_stat = 196,                 /* sys_stat  */
  YYSYMBOL_until_stat = 197,               /* until_stat  */
  YYSYMBOL_trap_stat = 198,                /* trap_stat  */
  YYSYMBOL_plusorminus = 199,              /* plusorminus  */
  YYSYMBOL_when_stat = 200,                /* when_stat  */
  YYSYMBOL_when_list = 201,                /* when_list  */
  YYSYMBOL_when_numlist = 202,             /* when_numlist  */
  YYSYMBOL_when_numitem = 203,             /* when_numitem  */
  YYSYMBOL_when_strlist = 204,             /* when_strlist  */
  YYSYMBOL_when_stritem = 205,             /* when_stritem  */
  YYSYMBOL_relop = 206,                    /* relop  */
  YYSYMBOL_while_stat = 207,               /* while_stat  */
  YYSYMBOL_repeat_stat = 208,              /* repeat_stat  */
  YYSYMBOL_write_stat = 209,               /* write_stat  */
  YYSYMBOL_assign_stat = 210,              /* assign_stat  */
  YYSYMBOL_assign_list = 211,              /* assign_list  */
  YYSYMBOL_assign_item = 212,              /* assign_item  */
  YYSYMBOL_nassign = 213,                  /* nassign  */
  YYSYMBOL_sassign = 214,                  /* sassign  */
  YYSYMBOL_assign1 = 215,                  /* assign1  */
  YYSYMBOL_assign2 = 216,                  /* assign2  */
  YYSYMBOL_label_stat = 217,               /* label_stat  */
  YYSYMBOL_xid = 218,                      /* xid  */
  YYSYMBOL_exp = 219,                      /* exp  */
  YYSYMBOL_numexp = 220,                   /* numexp  */
  YYSYMBOL_numexp2 = 221,                  /* numexp2  */
  YYSYMBOL_stringexp = 222,                /* stringexp  */
  YYSYMBOL_stringexp2 = 223,               /* stringexp2  */
  YYSYMBOL_opt_stringexp = 224,            /* opt_stringexp  */
  YYSYMBOL_string_factor = 225,            /* string_factor  */
  YYSYMBOL_opt_arg = 226,                  /* opt_arg  */
  YYSYMBOL_substr_spec = 227,              /* substr_spec  */
  YYSYMBOL_substr_spec2 = 228,             /* substr_spec2  */
  YYSYMBOL_optnumlvalue = 229,             /* optnumlvalue  */
  YYSYMBOL_optexp = 230,                   /* optexp  */
  YYSYMBOL_optid = 231,                    /* optid  */
  YYSYMBOL_optid2 = 232,                   /* optid2  */
  YYSYMBOL_optfile = 233,                  /* optfile  */
  YYSYMBOL_optfileS = 234,                 /* optfileS  */
  YYSYMBOL_lval_list = 235,                /* lval_list  */
  YYSYMBOL_lvalue = 236,                   /* lvalue  */
  YYSYMBOL_numlvalue = 237,                /* numlvalue  */
  YYSYMBOL_numlvalue2 = 238,               /* numlvalue2  */
  YYSYMBOL_strlvalue = 239,                /* strlvalue  */
  YYSYMBOL_strlvalue2 = 240,               /* strlvalue2  */
  YYSYMBOL_file_designator = 241,          /* file_designator  */
  YYSYMBOL_io_designator = 242,            /* io_designator  */
  YYSYMBOL_opt_external = 243,             /* opt_external  */
  YYSYMBOL_procfunc_head = 244,            /* procfunc_head  */
  YYSYMBOL_parmlist = 245,                 /* parmlist  */
  YYSYMBOL_parmitem = 246,                 /* parmitem  */
  YYSYMBOL_oneparm = 247,                  /* oneparm  */
  YYSYMBOL_id = 248,                       /* id  */
  YYSYMBOL_numid = 249,                    /* numid  */
  YYSYMBOL_opt_commalist = 250,            /* opt_commalist  */
  YYSYMBOL_exp_list = 251,                 /* exp_list  */
  YYSYMBOL_optsimple_stat = 252,           /* optsimple_stat  */
  YYSYMBOL_optof = 253,                    /* optof  */
  YYSYMBOL_optdo = 254,                    /* optdo  */
  YYSYMBOL_optthen = 255,                  /* optthen  */
  YYSYMBOL_optread_only = 256,             /* optread_only  */
  YYSYMBOL_optclosed = 257                 /* optclosed  */
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
#define YYFINAL  258
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1635

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  130
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  128
/* YYNRULES -- Number of rules.  */
#define YYNRULES  352
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  572

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   384


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
     125,   126,   127,   128,   129
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   242,   242,   248,   258,   265,   271,   277,   285,   287,
     291,   292,   294,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   351,
     352,   355,   359,   363,   367,   371,   375,   379,   383,   387,
     391,   395,   399,   403,   407,   413,   417,   421,   425,   429,
     435,   441,   445,   452,   460,   467,   474,   481,   488,   510,
     517,   524,   531,   538,   545,   553,   559,   564,   571,   575,
     579,   583,   587,   594,   601,   606,   613,   617,   621,   625,
     631,   632,   635,   637,   642,   648,   653,   660,   666,   672,
     680,   687,   694,   695,   698,   704,   708,   716,   720,   727,
     740,   744,   750,   755,   760,   771,   778,   785,   794,   801,
     810,   827,   833,   840,   845,   855,   867,   873,   879,   885,
     893,   899,   907,   914,   922,   930,   938,   950,   951,   954,
     958,   964,   968,   974,   978,   984,   986,   991,  1002,  1017,
    1023,  1030,  1038,  1045,  1050,  1057,  1065,  1072,  1078,  1082,
    1088,  1095,  1096,  1099,  1104,  1107,  1111,  1117,  1122,  1125,
    1129,  1133,  1139,  1143,  1147,  1151,  1155,  1159,  1165,  1172,
    1179,  1189,  1196,  1201,  1207,  1211,  1217,  1218,  1221,  1222,
    1228,  1232,  1238,  1242,  1248,  1254,  1258,  1262,  1268,  1269,
    1272,  1278,  1282,  1286,  1290,  1294,  1298,  1302,  1306,  1310,
    1314,  1318,  1322,  1326,  1330,  1334,  1338,  1342,  1346,  1350,
    1354,  1358,  1362,  1366,  1370,  1374,  1378,  1382,  1386,  1390,
    1394,  1395,  1399,  1403,  1407,  1411,  1415,  1419,  1423,  1427,
    1431,  1437,  1443,  1447,  1448,  1454,  1456,  1461,  1462,  1466,
    1470,  1474,  1478,  1482,  1486,  1490,  1494,  1500,  1505,  1510,
    1516,  1521,  1526,  1531,  1538,  1540,  1545,  1547,  1552,  1554,
    1559,  1561,  1566,  1573,  1578,  1579,  1580,  1583,  1587,  1593,
    1594,  1597,  1604,  1605,  1609,  1613,  1619,  1626,  1630,  1634,
    1638,  1642,  1648,  1653,  1660,  1665,  1670,  1675,  1682,  1690,
    1698,  1707,  1712,  1717,  1722,  1727,  1734,  1741,  1748,  1755,
    1762,  1771,  1776,  1783,  1784,  1787,  1788,  1791,  1792,  1795,
    1799,  1805,  1811,  1816,  1817,  1820,  1821,  1824,  1825,  1828,
    1833,  1838,  1843
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
  "stepSYM", "stopSYM", "spawnSYM", "waitSYM", "sysSYM", "syssSYM",
  "thenSYM", "timesSYM", "toSYM", "trapSYM", "unitSYM", "untilSYM",
  "usingSYM", "whenSYM", "whileSYM", "writeSYM", "qreadSYM", "qwriteSYM",
  "rnSYM", "rsSYM", "tnrnSYM", "tnrsSYM", "tsrnSYM", "tonrsSYM", "tsrsSYM",
  "tsrsnSYM", "lenSYM", "floatnumSYM", "idSYM", "intidSYM", "stringidSYM",
  "intnumSYM", "remSYM", "stringSYM", "USIGN", "$accept", "a_comal_line",
  "comal_line", "optrem", "program_line", "complex_stat", "simple_stat",
  "complex_1word", "simple_1word", "case_stat", "close_stat",
  "cursor_stat", "chdir_stat", "rmdir_stat", "mkdir_stat", "data_stat",
  "draw_stat", "tone_stat", "play_stat", "sleep_stat", "del_stat",
  "dir_stat", "unit_stat", "local_stat", "local_list", "local_item",
  "dim_stat", "dim_list", "dim_item", "of", "opt_dim_ensions",
  "dim_ensions", "dim_ension_list", "dim_ension", "elif_stat", "exit_stat",
  "ifwhen", "exec_stat", "spawn_stat", "wait_stat", "for_stat", "todownto",
  "optstep", "func_stat", "if_stat", "import_stat", "import_list",
  "input_stat", "input_modifier", "open_stat", "open_type", "queue_type",
  "os_stat", "print_stat", "printi", "prnum_list", "print_list", "pr_sep",
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

#define YYTABLE_NINF (-126)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     669,     6,  1507,   242,    11,  1507,  1507,   242,   159,   242,
    1507,  1507,  1507,  1507,  1507,  -369,  -369,   101,   176,  -369,
    -369,   -62,  -369,  -369,  -369,   -59,    52,   101,   176,  -369,
    1507,   176,    36,   181,  -369,   242,  -369,   190,   242,  -369,
    -369,  -369,     8,    99,   904,   -62,  -369,  1507,   242,   242,
     242,  -369,  1441,  1507,  1507,  1507,   105,   242,  1507,  1208,
    1507,    99,   112,    91,    93,   788,  -369,   158,   129,  -369,
      77,    77,  -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,
    -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,
    -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,
    -369,  -369,  -369,  1375,  -369,  -369,  -369,  -369,  -369,  -369,
    -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,   114,
    -369,  -369,    -8,   215,  -369,   164,  -369,  -369,  1507,  1507,
    1507,   137,   174,   180,  -369,  -369,   195,   208,   212,   217,
     218,   224,   231,  -369,   264,  -369,  -369,  -369,   179,  -369,
      51,  -369,   878,   267,  -369,  -369,   242,  -369,   -14,  -369,
    -369,  1507,   257,   878,  -369,   288,  -369,  -369,  -369,   -19,
     315,  -369,   269,  -369,  -369,   288,   288,   288,   288,   235,
    -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,
    -369,  1507,   187,   271,   235,   323,  -369,   131,  1507,  1507,
     330,   185,  -369,   175,   331,  -369,   269,  -369,  1507,  1507,
    -369,   271,  1507,   185,  -369,  -369,   105,   245,  -369,  -369,
    -369,  -369,  -369,  -369,  1507,  -369,    -6,   339,  -369,   288,
     156,  -369,  -369,  -369,  -369,  -369,   242,  -369,  -369,  -369,
    -369,   341,  -369,   343,  -369,  1507,  -369,  -369,   327,  1507,
    -369,  1507,  1507,   198,  -369,    77,  -369,  -369,  -369,  -369,
    -369,  -369,   242,    12,  -369,  1507,   185,  -369,  -369,  -369,
    -369,  1507,  -369,  -369,  -369,   242,  -369,   980,   497,  -369,
    -369,  1507,  1507,  1507,  1507,  1507,   242,  1507,  -369,   242,
    1507,  1507,  -369,  -369,  1507,  1507,  1507,  1507,  1507,  1507,
    1507,  1507,  1507,  1507,  1507,  1507,  1507,  1507,  1507,  1507,
    1507,  1507,   242,   242,   242,   242,   242,   242,   242,   242,
    1507,   198,  -369,   140,   288,  1507,  1507,  1507,  1507,   -31,
     159,  -369,  -369,  -369,  -369,  1507,   210,   348,   904,   176,
     176,  -369,   232,   241,  -369,   349,  -369,  -369,  -369,  1507,
     -31,   181,  -369,  -369,   351,   355,   348,   249,   349,  1507,
    -369,   -59,  -369,  -369,  -369,  -369,  1293,   415,  -369,  -369,
    -369,   904,   288,    17,    22,    34,    55,  1507,   360,   286,
      60,    71,  -369,   364,  -369,  -369,  1507,  -369,    12,  -369,
    -369,  -369,  -369,  -369,   538,    72,    73,  1036,  1081,   150,
    1126,   163,    85,  1171,   848,   132,   132,   303,   303,   132,
     325,   325,   325,   325,   325,    70,   303,   325,   132,   132,
      70,   303,   303,   -14,   -14,   -14,  -369,   -14,   -14,   -14,
     267,   303,   360,  -369,  -369,    96,  -369,   168,  -369,  -369,
    -369,  1507,  -369,    88,   176,   176,   261,   176,   106,  -369,
    -369,   326,  -369,   121,  -369,  -369,  -369,   323,   115,  -369,
    1507,  -369,  1507,   185,  -369,  1507,  -369,   242,   242,   121,
    -369,  1507,  -369,  -369,  -369,  1507,  -369,   242,  -369,  -369,
    -369,  -369,  -369,  -369,   373,  1507,  -369,  -369,   267,  1507,
    -369,  1507,  1507,  -369,  -369,  -369,  -369,  -369,  -369,  -369,
    -369,  -369,  -369,  -369,  1507,  -369,  1507,  1507,  -369,  -369,
    -369,  1507,  -369,  -369,  -369,  -369,   210,  -369,   347,   242,
     352,  -369,  -369,   376,   381,  -369,  -369,   383,   386,  -369,
     390,  -369,  -369,  -369,    12,  -369,  1216,  -369,  -369,  -369,
     309,  -369,   242,  -369,   242,  -369,  -369,    16,    20,  -369,
    1507,  -369,  -369,  1507,   327,  -369,  -369,  -369,  1507,  -369,
    -369,  -369,  -369,  -369,  -369,  -369,  -369,   904,   324,  -369,
    -369,  -369
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,     0,     0,     0,   296,     0,     0,     0,     0,   266,
       0,     0,     0,     0,     0,    61,    62,   285,   289,    64,
      66,   291,    76,    74,    68,     0,    77,     0,     0,    73,
       0,     0,   143,     0,    65,     0,    75,     0,     0,    70,
      78,   157,     0,   293,    71,   291,    79,   287,     0,     0,
       0,   158,   287,     0,   127,     0,    72,     0,     0,     0,
       0,     0,   215,   303,   307,    12,     8,     0,     0,     7,
       9,     9,    27,    60,    13,    28,    30,    29,    45,    38,
      14,    22,    54,    53,    46,    31,    33,    56,    34,    32,
      15,    16,    35,    47,    48,    17,    18,    19,    36,    37,
      39,    40,    41,   153,    20,    42,    43,    44,    49,    50,
      51,    52,    21,    55,    23,    24,    25,    57,    59,   201,
     203,    26,   302,     0,   301,     0,   306,     3,     0,     0,
       0,   255,     0,     0,   258,   271,     0,     0,     0,   278,
       0,     0,     0,   249,   215,   248,   273,   302,   344,   218,
     220,   219,   261,   263,   250,   267,     0,    84,   261,   294,
     295,     0,     0,     0,   340,    87,    92,   335,   336,     0,
     103,   105,     0,   265,    93,    88,    90,    89,    91,   348,
      69,   284,   334,    63,   288,   333,   290,    67,   124,   122,
     123,     0,     0,   323,   348,   137,   139,   331,     0,     0,
       0,     0,   141,    99,    95,    97,   113,    86,     0,     0,
     152,   323,     0,     0,   292,    77,     0,     0,   169,   286,
     170,    85,   172,   171,     0,   173,   302,     0,   128,   175,
       0,    94,   176,   194,   196,   192,     0,   197,   193,   195,
     180,   181,   184,   182,   188,     0,   186,   190,   346,     0,
     214,   338,   338,   338,   309,     9,    10,    11,     1,     2,
       5,     6,     0,   166,   162,     0,     0,   211,   212,   213,
     210,     0,   206,   207,   209,     0,   208,     0,     0,   246,
     247,     0,     0,     0,     0,     0,     0,     0,   272,     0,
       0,     0,   343,    80,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   268,     0,    82,     0,     0,     0,     0,   109,
       0,   106,   347,   120,   121,     0,     0,   352,   342,     0,
       0,   338,     0,     0,   142,   140,   298,   299,   300,     0,
     102,     0,    98,   112,     0,     0,   352,     0,   168,     0,
     174,     0,   179,   178,   177,   191,     0,     0,   185,   189,
     345,   342,   200,     0,     0,     0,     0,     0,   218,     0,
       0,     0,     4,     0,   163,   164,   165,   154,   156,   202,
     204,   205,   260,   276,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   227,   228,   235,   237,   231,
     221,   226,   224,   225,   223,   233,   238,   222,   229,   230,
     232,   236,   234,   239,   244,   242,   245,   243,   241,   240,
     262,   264,     0,    83,   339,     0,   116,   117,   107,   110,
     111,     0,   104,     0,     0,     0,     0,     0,     0,   325,
     326,   331,   351,   321,   341,   135,   138,   136,     0,   314,
       0,   316,     0,     0,   100,     0,    96,     0,     0,   321,
     312,     0,   199,   126,   183,     0,   187,     0,   198,   337,
     217,   216,   305,   304,   281,   282,   279,   311,   308,     0,
     161,     0,     0,   256,   259,   274,   254,   269,   251,   277,
     270,   275,   253,   252,     0,   114,     0,     0,   108,   131,
     130,     0,   330,   328,   329,   327,     0,   322,     0,     0,
       0,   134,   332,     0,     0,   297,   101,     0,     0,   167,
       0,   283,   280,   310,   166,   160,     0,   115,   119,   118,
     133,   324,     0,   318,     0,   315,   317,     0,     0,   313,
     165,   155,   257,     0,   346,   319,   320,   148,     0,   146,
     147,   144,   150,   151,   145,   159,   132,   342,   350,   129,
     349,   149
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -369,  -369,  -369,   -52,  -369,   342,    90,  -369,  -369,  -369,
    -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,
    -369,  -369,  -369,  -369,  -369,    57,  -369,  -369,    79,    61,
    -369,  -143,  -369,   -94,  -369,  -369,  -369,  -369,  -369,  -369,
    -369,  -369,  -369,  -369,  -369,  -369,    74,  -369,  -369,  -369,
    -369,  -369,  -369,  -369,  -369,  -369,   152,  -368,  -119,  -369,
    -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,  -369,
    -369,  -369,  -369,    56,  -369,    58,   -71,  -369,  -369,  -369,
    -369,  -369,   157,  -369,  -369,   -88,  -369,  -369,     3,     5,
      19,   357,    32,   130,  -369,   107,  -369,   -58,  -369,  -369,
     366,  -369,   379,  -369,  -369,   219,   -32,   -13,     0,  -188,
       1,   372,   332,   -35,   225,  -369,   -79,  -296,   -16,    -3,
    -230,    -2,  -355,  -369,  -116,   246,  -369,    83
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    67,    68,    69,   255,    70,   454,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,   204,   205,    89,   170,   171,   441,
     352,   329,   435,   436,    90,    91,   191,    92,    93,    94,
      95,   511,   554,    96,    97,    98,   195,    99,   201,   100,
     561,   564,   101,   102,   103,   534,   263,   386,   387,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   364,
     114,   240,   241,   242,   243,   244,   245,   115,   116,   117,
     118,   119,   120,   271,   275,   272,   273,   121,   147,   164,
     149,   150,   151,   163,   174,   153,   288,   322,   379,   180,
     220,   183,   187,   213,   161,   345,   346,   123,   154,   125,
     155,   214,   202,   521,   337,   448,   449,   196,   451,   185,
     373,   165,   455,   293,   371,   333,   571,   453
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     124,   126,   184,   122,   181,   172,   254,   148,   175,   176,
     177,   178,   193,   348,   192,   197,   478,   124,   260,   261,
     491,   557,   375,   380,   162,   348,   384,   124,   188,   331,
     206,   479,   -58,   179,  -125,   157,   326,   276,   439,   166,
     450,   173,   327,   456,   124,   126,   127,   122,   479,   194,
     328,   -81,   219,   229,   294,   295,   226,   219,   159,   160,
     350,   186,   319,   353,   144,   124,   126,   207,   122,   326,
     210,   440,   227,   228,   479,   296,   297,   232,   246,   248,
     221,   222,   223,   198,   199,   326,   326,   326,   320,   231,
      71,   247,   298,   299,   296,   297,   558,   559,   -58,   326,
    -125,   562,   300,   301,   335,   385,   189,   480,   264,   302,
     504,   458,   481,   303,   304,   509,   305,   -81,   306,   -58,
     516,  -125,   307,   308,   482,   250,   560,   309,   310,   479,
     563,   211,   152,   158,   217,   305,   152,   158,   -81,   158,
     152,   152,   152,   152,   340,   483,   212,   310,   230,   518,
     487,   515,   252,   311,   253,   257,   296,   297,   258,   324,
     190,   488,   494,   495,   200,   158,   550,   519,   158,   259,
     267,   274,   311,   251,   299,   501,   506,   152,   158,   158,
     158,   507,   152,   300,   301,   152,   505,   158,   347,   152,
     302,   510,   341,   267,   303,   304,   517,   305,   281,   306,
     347,   124,   126,   382,    66,   522,   270,   266,   309,   310,
     334,   377,   569,   124,   126,   520,   319,   342,   343,   362,
     450,   267,   268,   269,   144,    63,   319,   354,   355,   270,
     393,   357,   363,   152,   311,   282,   327,   208,   209,   319,
     498,   283,   320,   360,   349,   459,   460,   372,   292,   374,
     376,   381,   320,   500,   461,   462,   284,   270,   278,   128,
     444,   129,   470,   471,   368,   320,   124,   126,   365,   285,
     264,   325,   378,   286,   130,   348,   445,   369,   287,   289,
     395,   396,   167,   168,   169,   290,   323,   131,   402,   446,
     390,   152,   291,   447,   383,   475,   477,   132,   133,   167,
     168,   182,   326,   156,   167,   168,   203,   391,   144,    63,
      64,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,    63,    64,   145,   251,   146,   172,   321,   330,
     327,   434,   336,   167,   168,   182,   332,   339,   124,   126,
     432,   122,   133,   344,   433,   351,   437,   438,   206,   296,
     297,   359,   361,   370,   443,   366,   135,   367,   137,   452,
     139,   140,   141,   463,   473,   467,   158,    64,   464,   468,
     146,   124,   126,   485,   122,   152,   486,   489,   472,   152,
     310,   152,   152,   152,   514,   246,   531,   341,   304,   545,
     305,   490,   158,   542,   546,   152,   484,   547,   544,   247,
     548,   309,   310,   549,   553,   158,   570,   256,   466,   442,
     537,   465,   152,   152,   457,   551,   399,   388,   225,   401,
     152,   404,   474,   389,   218,   476,   430,   311,   512,   513,
     533,   525,   358,   249,   529,   265,   356,   541,   567,   469,
     338,     0,   423,   424,   425,   426,   427,   428,   429,     0,
     347,     0,     0,     0,     0,     0,   152,   233,     0,     0,
     508,     0,     0,   124,   126,     0,   234,   235,     0,     0,
       0,     0,   236,   237,     0,     0,   156,   238,     0,   523,
       0,   524,   239,     0,   526,   277,   279,   280,     0,     0,
     530,     0,     0,     0,   368,     0,   490,   158,     0,   527,
     528,     0,     0,     0,   532,     0,     0,     0,   535,   369,
       0,     0,     0,     0,     0,   133,   152,     0,     0,     0,
       0,     0,     0,   437,     0,   538,   539,     0,     0,   135,
     540,   137,     0,   139,   140,   141,     0,     0,     0,   312,
      64,   294,   295,   146,     0,     0,     0,     0,   313,   314,
       0,   543,   492,     0,   315,   316,     0,     0,     0,   317,
       0,     0,   296,   297,   318,     0,     0,   124,   126,   565,
     122,     0,   566,   319,   555,     0,   556,   568,     0,   298,
     299,     0,     0,     0,     0,     0,     0,   393,     0,   300,
     301,     0,     0,     0,     0,     0,   302,   158,   158,   320,
     303,   304,     0,   305,     0,   306,     0,   158,     0,   307,
     308,     0,     0,     0,   309,   310,     0,     0,     0,     0,
       0,   152,     0,     0,     0,     0,     0,     0,   493,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   394,     0,
     311,   397,   398,     0,   400,     0,     0,     0,   403,   158,
       0,   405,   406,   407,   408,   409,   410,   411,   412,   413,
     414,   415,   416,   417,   418,   419,   420,   421,   422,     0,
       1,     0,   158,     0,   158,     0,     0,   431,     2,     3,
       0,     4,     0,     0,     5,     6,     7,     8,     9,    10,
      11,    12,    13,     0,     0,     0,     0,     0,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    -9,
       0,     0,     0,    25,    26,     0,     0,     0,    27,    28,
       0,     0,    29,    30,    31,    32,     0,     0,    33,    34,
       0,     0,     0,    35,     0,     0,     0,    36,     0,    37,
       0,     0,    38,    39,    40,     0,     0,    41,    42,     0,
      43,     0,     0,    44,    45,    46,    47,    48,     0,     0,
      49,    50,    51,     0,     0,    52,    53,    54,    55,     0,
       0,     0,     0,    56,    57,    58,     0,    59,    60,    61,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    62,    63,    64,    65,    66,     2,     3,     0,
       4,     0,     0,     5,     6,     7,     8,     9,    10,    11,
      12,    13,     0,     0,     0,     0,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,     0,     0,
       0,     0,    25,    26,     0,     0,     0,    27,    28,     0,
       0,    29,    30,    31,    32,     0,     0,    33,    34,   536,
       0,     0,    35,     0,     0,     0,    36,     0,    37,     0,
       0,    38,    39,    40,     0,     0,    41,    42,     0,    43,
       0,     0,    44,    45,    46,    47,    48,     0,     0,    49,
      50,    51,     0,     0,    52,    53,    54,    55,     0,     0,
     312,     0,    56,    57,    58,     0,    59,    60,    61,   313,
     314,     0,     0,     0,     0,   315,   316,     0,     0,     0,
     317,    62,    63,    64,     3,   318,     4,     0,     0,     5,
     312,     7,     8,     9,   319,    11,    12,    13,     0,   313,
     314,     0,     0,     0,     0,   315,   316,     0,   503,     0,
     317,    22,     0,     0,     0,   318,     0,     0,    25,   215,
     320,     0,     0,     0,   319,     0,     0,     0,     0,    31,
      32,     0,     0,    33,     0,     0,     0,     0,    35,     0,
       0,     0,    36,     0,    37,     0,     0,    38,     0,    40,
     320,     0,    41,   294,   295,    43,     0,     0,     0,    45,
      46,    47,    48,     0,     0,    49,    50,    51,     0,     0,
      52,    53,    54,    55,   296,   297,     0,     0,   216,    57,
       0,     0,     0,     0,    61,     0,     0,     0,     0,     0,
       0,   298,   299,     0,     0,     0,     0,   144,    63,    64,
       0,   300,   301,     0,     0,     0,     0,     0,   302,   294,
     295,     0,   303,   304,     0,   305,     0,   306,     0,     0,
       0,   307,   308,     0,     0,     0,   309,   310,     0,     0,
     296,   297,     0,     0,     0,     0,     0,     0,     0,     0,
     392,     0,     0,     0,     0,     0,     0,   298,   299,     0,
       0,     0,   311,     0,   294,   295,     0,   300,   301,     0,
       0,     0,     0,     0,   302,     0,     0,     0,   303,   304,
       0,   305,     0,   306,     0,   296,   297,   307,   308,     0,
       0,     0,   309,   310,     0,     0,     0,     0,     0,     0,
       0,     0,   298,   299,     0,     0,   496,     0,     0,   294,
     295,     0,   300,   301,     0,     0,     0,     0,   311,   302,
       0,     0,     0,   303,   304,     0,   305,     0,   306,     0,
     296,   297,   307,   308,     0,     0,     0,   309,   310,     0,
       0,     0,     0,     0,     0,     0,     0,   298,   299,     0,
       0,   497,     0,     0,   294,   295,     0,   300,   301,     0,
       0,     0,     0,   311,   302,     0,     0,     0,   303,   304,
       0,   305,     0,   306,     0,   296,   297,   307,   308,     0,
       0,     0,   309,   310,     0,     0,     0,     0,     0,     0,
       0,     0,   298,   299,     0,     0,   499,     0,     0,   294,
     295,     0,   300,   301,     0,     0,     0,     0,   311,   302,
       0,     0,     0,   303,   304,     0,   305,     0,   306,     0,
     296,   297,   307,   308,     0,     0,     0,   309,   310,     0,
     233,     0,     0,     0,     0,     0,     0,   298,   299,   234,
     235,   502,     0,     0,     0,   236,   237,   300,   301,   128,
     238,   129,     0,   311,   302,   239,     0,     0,   303,   304,
       0,   305,     0,   306,   130,     0,     0,   307,   308,     0,
       0,     0,   309,   310,     0,     0,     0,   131,     0,     0,
       0,     0,     0,     0,     0,     0,   552,   132,   133,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   311,     0,
       0,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,    63,    64,   145,   233,   146,     0,     0,     0,
       0,     0,     0,     0,   234,   235,     0,     0,     0,     0,
       0,   237,     0,     0,   128,   238,   129,     0,     0,     0,
     239,     0,     0,     0,     0,     0,     0,     0,     0,   130,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   131,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   132,   133,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,    63,    64,   145,
       0,   146,   198,   199,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   128,     0,   129,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   130,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   131,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   132,   133,     0,     0,     0,     0,
       0,     0,   262,     0,     0,     0,     0,     0,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,    63,
      64,   145,   128,   146,   129,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   130,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     131,     0,     0,     0,     0,     0,     0,     0,   224,     0,
     132,   133,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,    63,    64,   145,   128,   146,
     129,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   130,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   131,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   132,   133,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,    63,    64,   145,     0,   146
};

static const yytype_int16 yycheck[] =
{
       0,     0,    18,     0,    17,     8,    64,     2,    10,    11,
      12,    13,    28,   201,    27,    31,   371,    17,    70,    71,
     388,     5,   252,   253,     5,   213,    14,    27,    25,   172,
      33,    14,    40,    14,    40,     3,    14,   125,    69,     7,
     336,     9,    61,   339,    44,    44,    40,    44,    14,    30,
      69,    40,    47,    55,     3,     4,    53,    52,    47,    48,
     203,   123,    76,   206,   123,    65,    65,    35,    65,    14,
      38,   102,    53,    54,    14,    24,    25,    58,    59,    60,
      48,    49,    50,    47,    48,    14,    14,    14,   102,    57,
       0,    59,    41,    42,    24,    25,    80,    81,   106,    14,
     106,    81,    51,    52,   192,    93,    54,    90,   103,    58,
      14,   341,    90,    62,    63,    27,    65,   106,    67,   127,
      14,   127,    71,    72,    90,    13,   110,    76,    77,    14,
     110,   123,     2,     3,    44,    65,     6,     7,   127,     9,
      10,    11,    12,    13,    13,    90,    47,    77,    43,    28,
      90,   447,    61,   102,    61,    65,    24,    25,     0,   161,
     108,    90,    90,    90,   128,    35,   534,    46,    38,    40,
       6,     7,   102,    61,    42,    90,     8,    47,    48,    49,
      50,    13,    52,    51,    52,    55,    90,    57,   201,    59,
      58,   103,    61,     6,    62,    63,    90,    65,    61,    67,
     213,   201,   201,   255,   127,    90,    42,    93,    76,    77,
     191,    13,   567,   213,   213,    94,    76,   198,   199,    63,
     516,     6,     7,     8,   123,   124,    76,   208,   209,    42,
      90,   212,    76,   103,   102,    61,    61,    47,    48,    76,
      90,    61,   102,   224,    69,    13,    14,   249,    69,   251,
     252,   253,   102,    90,    13,    14,    61,    42,   128,    61,
      50,    63,    13,    14,   245,   102,   266,   266,   236,    61,
     265,    14,   253,    61,    76,   463,    66,   245,    61,    61,
     282,   283,   123,   124,   125,    61,   156,    89,   290,    79,
     271,   161,    61,    83,   262,   366,   367,    99,   100,   123,
     124,   125,    14,    61,   123,   124,   125,   275,   123,   124,
     125,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,    61,   128,   330,    61,    14,
      61,   326,    61,   123,   124,   125,   101,    14,   338,   338,
     321,   338,   100,    13,   325,    14,   327,   328,   351,    24,
      25,   106,    13,    26,   335,    14,   114,    14,   116,    11,
     118,   119,   120,    14,   361,    14,   236,   125,   349,    14,
     128,   371,   371,    13,   371,   245,    90,    13,   359,   249,
      77,   251,   252,   253,   123,   366,    13,    61,    63,    13,
      65,   386,   262,    46,    13,   265,   377,    14,    46,   367,
      14,    76,    77,    13,    95,   275,    82,    65,   351,   330,
     504,   350,   282,   283,   340,   534,   286,   265,    52,   289,
     290,   291,   366,   266,    45,   367,   319,   102,   444,   445,
     488,   463,   213,    61,   469,   103,   211,   516,   554,   356,
     194,    -1,   312,   313,   314,   315,   316,   317,   318,    -1,
     463,    -1,    -1,    -1,    -1,    -1,   326,    42,    -1,    -1,
     441,    -1,    -1,   463,   463,    -1,    51,    52,    -1,    -1,
      -1,    -1,    57,    58,    -1,    -1,    61,    62,    -1,   460,
      -1,   462,    67,    -1,   465,   128,   129,   130,    -1,    -1,
     471,    -1,    -1,    -1,   475,    -1,   491,   367,    -1,   467,
     468,    -1,    -1,    -1,   485,    -1,    -1,    -1,   489,   477,
      -1,    -1,    -1,    -1,    -1,   100,   386,    -1,    -1,    -1,
      -1,    -1,    -1,   504,    -1,   506,   507,    -1,    -1,   114,
     511,   116,    -1,   118,   119,   120,    -1,    -1,    -1,    42,
     125,     3,     4,   128,    -1,    -1,    -1,    -1,    51,    52,
      -1,   519,    14,    -1,    57,    58,    -1,    -1,    -1,    62,
      -1,    -1,    24,    25,    67,    -1,    -1,   567,   567,   550,
     567,    -1,   553,    76,   542,    -1,   544,   558,    -1,    41,
      42,    -1,    -1,    -1,    -1,    -1,    -1,    90,    -1,    51,
      52,    -1,    -1,    -1,    -1,    -1,    58,   467,   468,   102,
      62,    63,    -1,    65,    -1,    67,    -1,   477,    -1,    71,
      72,    -1,    -1,    -1,    76,    77,    -1,    -1,    -1,    -1,
      -1,   491,    -1,    -1,    -1,    -1,    -1,    -1,    90,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   281,    -1,
     102,   284,   285,    -1,   287,    -1,    -1,    -1,   291,   519,
      -1,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,    -1,
       1,    -1,   542,    -1,   544,    -1,    -1,   320,     9,    10,
      -1,    12,    -1,    -1,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    -1,    -1,    -1,    -1,    -1,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      -1,    -1,    -1,    44,    45,    -1,    -1,    -1,    49,    50,
      -1,    -1,    53,    54,    55,    56,    -1,    -1,    59,    60,
      -1,    -1,    -1,    64,    -1,    -1,    -1,    68,    -1,    70,
      -1,    -1,    73,    74,    75,    -1,    -1,    78,    79,    -1,
      81,    -1,    -1,    84,    85,    86,    87,    88,    -1,    -1,
      91,    92,    93,    -1,    -1,    96,    97,    98,    99,    -1,
      -1,    -1,    -1,   104,   105,   106,    -1,   108,   109,   110,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   123,   124,   125,   126,   127,     9,    10,    -1,
      12,    -1,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    -1,    -1,
      -1,    -1,    44,    45,    -1,    -1,    -1,    49,    50,    -1,
      -1,    53,    54,    55,    56,    -1,    -1,    59,    60,   492,
      -1,    -1,    64,    -1,    -1,    -1,    68,    -1,    70,    -1,
      -1,    73,    74,    75,    -1,    -1,    78,    79,    -1,    81,
      -1,    -1,    84,    85,    86,    87,    88,    -1,    -1,    91,
      92,    93,    -1,    -1,    96,    97,    98,    99,    -1,    -1,
      42,    -1,   104,   105,   106,    -1,   108,   109,   110,    51,
      52,    -1,    -1,    -1,    -1,    57,    58,    -1,    -1,    -1,
      62,   123,   124,   125,    10,    67,    12,    -1,    -1,    15,
      42,    17,    18,    19,    76,    21,    22,    23,    -1,    51,
      52,    -1,    -1,    -1,    -1,    57,    58,    -1,    90,    -1,
      62,    37,    -1,    -1,    -1,    67,    -1,    -1,    44,    45,
     102,    -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,    55,
      56,    -1,    -1,    59,    -1,    -1,    -1,    -1,    64,    -1,
      -1,    -1,    68,    -1,    70,    -1,    -1,    73,    -1,    75,
     102,    -1,    78,     3,     4,    81,    -1,    -1,    -1,    85,
      86,    87,    88,    -1,    -1,    91,    92,    93,    -1,    -1,
      96,    97,    98,    99,    24,    25,    -1,    -1,   104,   105,
      -1,    -1,    -1,    -1,   110,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    42,    -1,    -1,    -1,    -1,   123,   124,   125,
      -1,    51,    52,    -1,    -1,    -1,    -1,    -1,    58,     3,
       4,    -1,    62,    63,    -1,    65,    -1,    67,    -1,    -1,
      -1,    71,    72,    -1,    -1,    -1,    76,    77,    -1,    -1,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      90,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    -1,
      -1,    -1,   102,    -1,     3,     4,    -1,    51,    52,    -1,
      -1,    -1,    -1,    -1,    58,    -1,    -1,    -1,    62,    63,
      -1,    65,    -1,    67,    -1,    24,    25,    71,    72,    -1,
      -1,    -1,    76,    77,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    42,    -1,    -1,    90,    -1,    -1,     3,
       4,    -1,    51,    52,    -1,    -1,    -1,    -1,   102,    58,
      -1,    -1,    -1,    62,    63,    -1,    65,    -1,    67,    -1,
      24,    25,    71,    72,    -1,    -1,    -1,    76,    77,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    -1,
      -1,    90,    -1,    -1,     3,     4,    -1,    51,    52,    -1,
      -1,    -1,    -1,   102,    58,    -1,    -1,    -1,    62,    63,
      -1,    65,    -1,    67,    -1,    24,    25,    71,    72,    -1,
      -1,    -1,    76,    77,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    42,    -1,    -1,    90,    -1,    -1,     3,
       4,    -1,    51,    52,    -1,    -1,    -1,    -1,   102,    58,
      -1,    -1,    -1,    62,    63,    -1,    65,    -1,    67,    -1,
      24,    25,    71,    72,    -1,    -1,    -1,    76,    77,    -1,
      42,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    51,
      52,    90,    -1,    -1,    -1,    57,    58,    51,    52,    61,
      62,    63,    -1,   102,    58,    67,    -1,    -1,    62,    63,
      -1,    65,    -1,    67,    76,    -1,    -1,    71,    72,    -1,
      -1,    -1,    76,    77,    -1,    -1,    -1,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    90,    99,   100,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,
      -1,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,    42,   128,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    51,    52,    -1,    -1,    -1,    -1,
      -1,    58,    -1,    -1,    61,    62,    63,    -1,    -1,    -1,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    99,   100,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
      -1,   128,    47,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    61,    -1,    63,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    99,   100,    -1,    -1,    -1,    -1,
      -1,    -1,   107,    -1,    -1,    -1,    -1,    -1,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,    61,   128,    63,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    97,    -1,
      99,   100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,    61,   128,
      63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    99,   100,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,    -1,   128
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,     1,     9,    10,    12,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    44,    45,    49,    50,    53,
      54,    55,    56,    59,    60,    64,    68,    70,    73,    74,
      75,    78,    79,    81,    84,    85,    86,    87,    88,    91,
      92,    93,    96,    97,    98,    99,   104,   105,   106,   108,
     109,   110,   123,   124,   125,   126,   127,   131,   132,   133,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   156,
     164,   165,   167,   168,   169,   170,   173,   174,   175,   177,
     179,   182,   183,   184,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   200,   207,   208,   209,   210,   211,
     212,   217,   218,   237,   238,   239,   240,    40,    61,    63,
      76,    89,    99,   100,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   126,   128,   218,   219,   220,
     221,   222,   223,   225,   238,   240,    61,   222,   223,    47,
      48,   234,   220,   223,   219,   251,   222,   123,   124,   125,
     157,   158,   249,   222,   224,   251,   251,   251,   251,   220,
     229,   237,   125,   231,   248,   249,   123,   232,   218,    54,
     108,   166,   237,   248,   220,   176,   247,   248,    47,    48,
     128,   178,   242,   125,   154,   155,   249,   222,    47,    48,
     222,   123,    47,   233,   241,    45,   104,   136,   232,   219,
     230,   222,   222,   222,    97,   230,   218,   220,   220,   251,
      43,   222,   220,    42,    51,    52,    57,    58,    62,    67,
     201,   202,   203,   204,   205,   206,   220,   222,   220,   241,
      13,    61,    61,    61,   227,   134,   135,   136,     0,    40,
     133,   133,   107,   186,   219,   242,    93,     6,     7,     8,
      42,   213,   215,   216,     7,   214,   215,   221,   223,   221,
     221,    61,    61,    61,    61,    61,    61,    61,   226,    61,
      61,    61,    69,   253,     3,     4,    24,    25,    41,    42,
      51,    52,    58,    62,    63,    65,    67,    71,    72,    76,
      77,   102,    42,    51,    52,    57,    58,    62,    67,    76,
     102,    61,   227,   223,   251,    14,    14,    61,    69,   161,
      14,   161,   101,   255,   220,   215,    61,   244,   255,    14,
      13,    61,   220,   220,    13,   235,   236,   237,   239,    69,
     161,    14,   160,   161,   220,   220,   244,   220,   235,   106,
     220,    13,    63,    76,   199,   222,    14,    14,   220,   222,
      26,   254,   251,   250,   251,   250,   251,    13,   220,   228,
     250,   251,   133,   222,    14,    93,   187,   188,   186,   212,
     220,   222,    90,    90,   221,   251,   251,   221,   221,   223,
     221,   223,   251,   221,   223,   221,   221,   221,   221,   221,
     221,   221,   221,   221,   221,   221,   221,   221,   221,   221,
     221,   221,   221,   223,   223,   223,   223,   223,   223,   223,
     225,   221,   220,   220,   219,   162,   163,   220,   220,    69,
     102,   159,   158,   220,    50,    66,    79,    83,   245,   246,
     247,   248,    11,   257,   136,   252,   247,   176,   250,    13,
      14,    13,    14,    14,   220,   159,   155,    14,    14,   257,
      13,    14,   220,   218,   203,   206,   205,   206,   252,    14,
      90,    90,    90,    90,   220,    13,    90,    90,    90,    13,
     219,   187,    14,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    14,    90,     8,    13,   220,    27,
     103,   171,   248,   248,   123,   247,    14,    90,    28,    46,
      94,   243,    90,   220,   220,   236,   220,   222,   222,   243,
     220,    13,   220,   227,   185,   220,   221,   163,   220,   220,
     220,   246,    46,   222,    46,    13,    13,    14,    14,    13,
     187,   188,    90,    95,   172,   222,   222,     5,    80,    81,
     110,   180,    81,   110,   181,   220,   220,   254,   220,   252,
      82,   256
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int16 yyr1[] =
{
       0,   130,   131,   131,   132,   132,   132,   132,   133,   133,
     134,   134,   134,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   138,   138,   138,   138,   138,
     139,   140,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   154,   155,   155,
     155,   155,   155,   156,   157,   157,   158,   158,   158,   158,
     159,   159,   160,   160,   161,   162,   162,   163,   163,   163,
     164,   165,   166,   166,   167,   168,   168,   169,   169,   170,
     171,   171,   172,   172,   173,   174,   175,   175,   176,   176,
     177,   178,   178,   178,   179,   179,   180,   180,   180,   180,
     181,   181,   182,   183,   183,   183,   183,   184,   184,   185,
     185,   186,   186,   187,   187,   188,   188,   189,   190,   191,
     192,   193,   194,   195,   195,   196,   197,   198,   199,   199,
     200,   201,   201,   202,   202,   203,   203,   204,   204,   205,
     205,   205,   206,   206,   206,   206,   206,   206,   207,   208,
     209,   210,   211,   211,   212,   212,   213,   213,   214,   214,
     215,   215,   216,   216,   217,   218,   218,   218,   219,   219,
     220,   221,   221,   221,   221,   221,   221,   221,   221,   221,
     221,   221,   221,   221,   221,   221,   221,   221,   221,   221,
     221,   221,   221,   221,   221,   221,   221,   221,   221,   221,
     221,   221,   221,   221,   221,   221,   221,   221,   221,   221,
     221,   222,   223,   223,   223,   224,   224,   225,   225,   225,
     225,   225,   225,   225,   225,   225,   225,   226,   226,   227,
     228,   228,   228,   228,   229,   229,   230,   230,   231,   231,
     232,   232,   233,   233,   234,   234,   234,   235,   235,   236,
     236,   237,   238,   238,   238,   238,   239,   240,   240,   240,
     240,   240,   241,   241,   242,   242,   242,   242,   243,   243,
     243,   243,   244,   244,   245,   245,   246,   246,   246,   246,
     246,   247,   247,   248,   248,   249,   249,   250,   250,   251,
     251,   252,   252,   253,   253,   254,   254,   255,   255,   256,
     256,   257,   257
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
       1,     1,     1,     2,     1,     1,     1,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     3,     4,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     3,     1,     2,     1,
       3,     4,     2,     2,     3,     1,     2,     3,     4,     2,
       1,     1,     1,     0,     3,     3,     1,     1,     3,     3,
       3,     3,     1,     1,     2,     2,     4,     1,     2,     9,
       1,     1,     2,     0,     5,     4,     4,     2,     3,     1,
       3,     1,     2,     0,     7,     7,     1,     1,     1,     3,
       1,     1,     2,     1,     3,     6,     3,     1,     1,     3,
       1,     3,     1,     1,     1,     1,     0,     5,     3,     2,
       2,     2,     2,     2,     3,     2,     2,     3,     1,     1,
       2,     1,     1,     3,     1,     2,     1,     3,     1,     2,
       1,     2,     1,     1,     1,     1,     1,     1,     4,     4,
       3,     1,     3,     1,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     4,     4,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     1,     1,
       1,     4,     4,     4,     4,     1,     4,     6,     1,     4,
       3,     1,     3,     1,     3,     1,     0,     1,     2,     4,
       4,     1,     2,     1,     4,     4,     3,     3,     0,     3,
       3,     2,     2,     3,     1,     0,     1,     0,     1,     0,
       1,     0,     1,     0,     1,     1,     0,     3,     1,     1,
       1,     1,     1,     1,     4,     4,     1,     1,     4,     2,
       5,     4,     3,     5,     3,     5,     3,     5,     2,     3,
       3,     0,     3,     0,     3,     1,     1,     2,     2,     2,
       2,     1,     4,     1,     1,     1,     1,     2,     0,     3,
       1,     1,     0,     1,     0,     1,     0,     1,     0,     1,
       0,     1,     0
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
#line 243 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				c_line_modern = (comal::ComalLine*)(yyvsp[-1].pcl_modern);
				c_line.cmd=0;  /* legacy path: cmd cleared; content in c_line_modern */
				YYACCEPT;
			}
#line 2036 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 3: /* a_comal_line: error eolnSYM  */
#line 249 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				p_error("Syntax error");
				yyerrok;
				c_line.cmd=0;
				c_line_modern = nullptr;
				YYACCEPT;
			}
#line 2048 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 4: /* comal_line: intnumSYM program_line optrem  */
#line 259 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				comal::ComalLine* cl = (comal::ComalLine*)(yyvsp[-1].pcl_modern);
				cl->setLineData(new comal::ComalLineData((yyvsp[-2].num), 0, (yyvsp[0].str)));
				cl->setLinePtr(nullptr);
				(yyval.pcl_modern) = (void*)cl;
			}
#line 2059 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 5: /* comal_line: complex_stat optrem  */
#line 266 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				comal::ComalLine* cl = (comal::ComalLine*)(yyvsp[-1].pcl_modern);
				if ((yyvsp[0].str)) cl->setLineData(new comal::ComalLineData(0, 0, (yyvsp[0].str)));
				(yyval.pcl_modern) = (void*)cl;
			}
#line 2069 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 6: /* comal_line: simple_stat optrem  */
#line 272 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				comal::ComalLine* cl = (comal::ComalLine*)(yyvsp[-1].pcl_modern);
				if ((yyvsp[0].str)) cl->setLineData(new comal::ComalLineData(0, 0, (yyvsp[0].str)));
				(yyval.pcl_modern) = (void*)cl;
			}
#line 2079 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 7: /* comal_line: optrem  */
#line 278 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				comal::ComalLine* cl = comal::build_empty_line();
				if ((yyvsp[0].str)) cl->setLineData(new comal::ComalLineData(0, 0, (yyvsp[0].str)));
				(yyval.pcl_modern) = (void*)cl;
			}
#line 2089 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 9: /* optrem: %empty  */
#line 287 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.str)=NULL;
			}
#line 2097 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 12: /* program_line: %empty  */
#line 294 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_empty_line();
			}
#line 2105 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 58: /* simple_stat: xid  */
#line 348 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_exec_line(comal::convert_expression((yyvsp[0].exp)));
			}
#line 2113 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 61: /* complex_1word: elseSYM  */
#line 356 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_simple_keyword_line(comal::StatementType::Else);
			}
#line 2121 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 62: /* complex_1word: endcaseSYM  */
#line 360 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_simple_keyword_line(comal::StatementType::EndCase);
			}
#line 2129 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 63: /* complex_1word: endfuncSYM optid  */
#line 364 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_simple_keyword_line(comal::StatementType::EndFunc);
			}
#line 2137 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 64: /* complex_1word: endifSYM  */
#line 368 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_simple_keyword_line(comal::StatementType::EndIf);
			}
#line 2145 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 65: /* complex_1word: loopSYM  */
#line 372 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_simple_keyword_line(comal::StatementType::Loop);
			}
#line 2153 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 66: /* complex_1word: endloopSYM  */
#line 376 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_simple_keyword_line(comal::StatementType::EndLoop);
			}
#line 2161 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 67: /* complex_1word: endprocSYM optid2  */
#line 380 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_simple_keyword_line(comal::StatementType::EndProc);
			}
#line 2169 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 68: /* complex_1word: endwhileSYM  */
#line 384 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_simple_keyword_line(comal::StatementType::EndWhile);
			}
#line 2177 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 69: /* complex_1word: endforSYM optnumlvalue  */
#line 388 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_simple_keyword_line(comal::StatementType::EndFor);
			}
#line 2185 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 70: /* complex_1word: otherwiseSYM  */
#line 392 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_simple_keyword_line(comal::StatementType::Otherwise);
			}
#line 2193 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 71: /* complex_1word: repeatSYM  */
#line 396 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_repeat_line(comal::IfWhileRec{nullptr, nullptr});
			}
#line 2201 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 72: /* complex_1word: trapSYM  */
#line 400 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_trap_line(comal::TrapRec{0});
			}
#line 2209 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 73: /* complex_1word: handlerSYM  */
#line 404 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_simple_keyword_line(comal::StatementType::Handler);
			}
#line 2217 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 74: /* complex_1word: endtrapSYM  */
#line 408 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_simple_keyword_line(comal::StatementType::EndTrap);
			}
#line 2225 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 75: /* simple_1word: nullSYM  */
#line 414 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_simple_keyword_line(comal::StatementType::Null);
			}
#line 2233 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 76: /* simple_1word: endSYM  */
#line 418 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_simple_keyword_line(comal::StatementType::End);
			}
#line 2241 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 77: /* simple_1word: exitSYM  */
#line 422 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_single_exp_line(comal::StatementType::Exit, nullptr);
			}
#line 2249 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 78: /* simple_1word: pageSYM  */
#line 426 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_simple_keyword_line(comal::StatementType::Page);
			}
#line 2257 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 79: /* simple_1word: retrySYM  */
#line 430 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_simple_keyword_line(comal::StatementType::Retry);
			}
#line 2265 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 80: /* case_stat: caseSYM exp optof  */
#line 436 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_case_line(comal::convert_expression((yyvsp[-1].exp)));
			}
#line 2273 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 81: /* close_stat: closeSYM  */
#line 442 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_close_line(nullptr);
			}
#line 2281 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 82: /* close_stat: closeSYM optfileS exp_list  */
#line 446 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_close_line(
					comal::convert_exp_list(PARS_REVERSE(struct exp_list, (yyvsp[0].expptr))));
			}
#line 2290 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 83: /* cursor_stat: cursorSYM numexp commaSYM numexp  */
#line 453 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_cursor_line(
					comal::convert_expression((yyvsp[-2].exp)),
					comal::convert_expression((yyvsp[0].exp)));
			}
#line 2300 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 84: /* chdir_stat: chdirSYM stringexp  */
#line 461 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_single_exp_line(comal::StatementType::Chdir,
					comal::convert_expression((yyvsp[0].exp)));
			}
#line 2309 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 85: /* rmdir_stat: rmdirSYM stringexp  */
#line 468 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_single_exp_line(comal::StatementType::Rmdir,
					comal::convert_expression((yyvsp[0].exp)));
			}
#line 2318 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 86: /* mkdir_stat: mkdirSYM stringexp  */
#line 475 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_single_exp_line(comal::StatementType::Mkdir,
					comal::convert_expression((yyvsp[0].exp)));
			}
#line 2327 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 87: /* data_stat: dataSYM exp_list  */
#line 482 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_data_line(
					comal::convert_exp_list(PARS_REVERSE(struct exp_list, (yyvsp[0].expptr))));
			}
#line 2336 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 88: /* draw_stat: drawSYM exp_list  */
#line 489 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				struct exp_list* rev = PARS_REVERSE(struct exp_list, (yyvsp[0].expptr));
				/* Auto-quote: if the first expression is a bare
				   identifier (no subscripts), treat it as a
				   string constant — e.g. DRAW circle, 100, 200, 50
				   becomes DRAW "circle", 100, 200, 50 */
				struct exp_list *first = rev;
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
				(yyval.pcl_modern) = (void*)comal::build_draw_line(comal::convert_exp_list(rev));
			}
#line 2360 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 89: /* tone_stat: toneSYM exp_list  */
#line 511 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                                {
				(yyval.pcl_modern) = (void*)comal::build_tone_line(
					comal::convert_exp_list(PARS_REVERSE(struct exp_list, (yyvsp[0].expptr))));
			}
#line 2369 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 90: /* play_stat: playSYM exp_list  */
#line 518 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                                {
				(yyval.pcl_modern) = (void*)comal::build_play_line(
					comal::convert_exp_list(PARS_REVERSE(struct exp_list, (yyvsp[0].expptr))));
			}
#line 2378 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 91: /* sleep_stat: sleepSYM exp_list  */
#line 525 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
			(yyval.pcl_modern) = (void*)comal::build_sleep_line(
				comal::convert_exp_list(PARS_REVERSE(struct exp_list, (yyvsp[0].expptr))));
		}
#line 2387 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 92: /* del_stat: delSYM stringexp  */
#line 532 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_single_exp_line(comal::StatementType::Del,
					comal::convert_expression((yyvsp[0].exp)));
			}
#line 2396 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 93: /* dir_stat: dirSYM opt_stringexp  */
#line 539 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_single_exp_line(comal::StatementType::Dir,
					comal::convert_expression((yyvsp[0].exp)));
			}
#line 2405 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 94: /* unit_stat: unitSYM stringexp  */
#line 546 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_single_exp_line(comal::StatementType::Unit,
					comal::convert_expression((yyvsp[0].exp)));
			}
#line 2414 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 95: /* local_stat: localSYM local_list  */
#line 554 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_local_line(
					comal::convert_dim_list(PARS_REVERSE(struct dim_list, (yyvsp[0].dimptr))));
			}
#line 2423 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 96: /* local_list: local_list commaSYM local_item  */
#line 560 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=(yyvsp[0].dimptr);
				(yyval.dimptr)->next=(yyvsp[-2].dimptr);
			}
#line 2432 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 97: /* local_list: local_item  */
#line 565 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=(yyvsp[0].dimptr);
				(yyval.dimptr)->next=NULL;
			}
#line 2441 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 98: /* local_item: numid opt_dim_ensions  */
#line 572 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[-1].id),NULL,(yyvsp[0].dimensionptr));
			}
#line 2449 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 99: /* local_item: stringidSYM  */
#line 576 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[0].id),NULL,NULL);
			}
#line 2457 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 100: /* local_item: stringidSYM ofSYM numexp  */
#line 580 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[-2].id),(yyvsp[0].exp),NULL);
			}
#line 2465 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 101: /* local_item: stringidSYM dim_ensions of numexp  */
#line 584 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[-3].id),(yyvsp[0].exp),(yyvsp[-2].dimensionptr));
			}
#line 2473 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 102: /* local_item: stringidSYM dim_ensions  */
#line 588 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[-1].id),NULL,(yyvsp[0].dimensionptr));
			}
#line 2481 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 103: /* dim_stat: dimSYM dim_list  */
#line 595 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_dim_line(
					comal::convert_dim_list(PARS_REVERSE(struct dim_list, (yyvsp[0].dimptr))));
			}
#line 2490 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 104: /* dim_list: dim_list commaSYM dim_item  */
#line 602 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=(yyvsp[0].dimptr);
				(yyval.dimptr)->next=(yyvsp[-2].dimptr);
			}
#line 2499 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 105: /* dim_list: dim_item  */
#line 607 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=(yyvsp[0].dimptr);
				(yyval.dimptr)->next=NULL;
			}
#line 2508 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 106: /* dim_item: numid dim_ensions  */
#line 614 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[-1].id),NULL,(yyvsp[0].dimensionptr));
			}
#line 2516 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 107: /* dim_item: stringidSYM ofSYM numexp  */
#line 618 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[-2].id),(yyvsp[0].exp),NULL);
			}
#line 2524 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 108: /* dim_item: stringidSYM dim_ensions of numexp  */
#line 622 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[-3].id),(yyvsp[0].exp),(yyvsp[-2].dimensionptr));
			}
#line 2532 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 109: /* dim_item: stringidSYM dim_ensions  */
#line 626 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimptr)=pars_dimlist_item((yyvsp[-1].id),NULL,(yyvsp[0].dimensionptr));
			}
#line 2540 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 113: /* opt_dim_ensions: %empty  */
#line 637 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimensionptr)=NULL;
			}
#line 2548 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 114: /* dim_ensions: lparenSYM dim_ension_list rparenSYM  */
#line 643 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimensionptr)=(yyvsp[-1].dimensionptr);
			}
#line 2556 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 115: /* dim_ension_list: dim_ension_list commaSYM dim_ension  */
#line 649 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimensionptr)=(yyvsp[0].dimensionptr);
				(yyval.dimensionptr)->next=(yyvsp[-2].dimensionptr);
			}
#line 2565 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 116: /* dim_ension_list: dim_ension  */
#line 654 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimensionptr)=(yyvsp[0].dimensionptr);
				(yyval.dimensionptr)->next=NULL;
			}
#line 2574 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 117: /* dim_ension: numexp  */
#line 661 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimensionptr)=PARS_ALLOC(struct dim_ension);
				(yyval.dimensionptr)->bottom=NULL;
				(yyval.dimensionptr)->top=(yyvsp[0].exp);
			}
#line 2584 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 118: /* dim_ension: numexp colonSYM numexp  */
#line 667 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimensionptr)=PARS_ALLOC(struct dim_ension);
				(yyval.dimensionptr)->bottom=(yyvsp[-2].exp);
				(yyval.dimensionptr)->top=(yyvsp[0].exp);
			}
#line 2594 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 119: /* dim_ension: numexp becminusSYM numexp  */
#line 673 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.dimensionptr)=PARS_ALLOC(struct dim_ension);
				(yyval.dimensionptr)->bottom=(yyvsp[-2].exp);
				(yyval.dimensionptr)->top=pars_exp_unary(minusSYM,(yyvsp[0].exp));
			}
#line 2604 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 120: /* elif_stat: elifSYM numexp optthen  */
#line 681 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_single_exp_line(comal::StatementType::Elif,
					comal::convert_expression((yyvsp[-1].exp)));
			}
#line 2613 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 121: /* exit_stat: exitSYM ifwhen numexp  */
#line 688 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_single_exp_line(comal::StatementType::Exit,
					comal::convert_expression((yyvsp[0].exp)));
			}
#line 2622 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 124: /* exec_stat: execSYM xid  */
#line 699 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_exec_line(comal::convert_expression((yyvsp[0].exp)));
			}
#line 2630 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 125: /* spawn_stat: spawnSYM xid  */
#line 705 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_spawn_line(comal::convert_expression((yyvsp[0].exp)));
			}
#line 2638 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 126: /* spawn_stat: spawnSYM numexp colonSYM xid  */
#line 709 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_spawn_handle_line(
					comal::convert_expression((yyvsp[-2].exp)),
					comal::convert_expression((yyvsp[0].exp)));
			}
#line 2648 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 127: /* wait_stat: waitSYM  */
#line 717 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_single_exp_line(comal::StatementType::Wait, nullptr);
			}
#line 2656 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 128: /* wait_stat: waitSYM numexp  */
#line 721 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_single_exp_line(comal::StatementType::Wait,
					comal::convert_expression((yyvsp[0].exp)));
			}
#line 2665 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 129: /* for_stat: forSYM numlvalue assign1 numexp todownto numexp optstep optdo optsimple_stat  */
#line 728 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				comal::ForRec fr;
				fr.lval = comal::convert_expression((yyvsp[-7].exp));
				fr.from = comal::convert_expression((yyvsp[-5].exp));
				fr.mode = (yyvsp[-4].inum);
				fr.to   = comal::convert_expression((yyvsp[-3].exp));
				fr.step = comal::convert_expression((yyvsp[-2].exp));
				fr.stat = (comal::ComalLine*)(yyvsp[0].pcl_modern);
				(yyval.pcl_modern) = (void*)comal::build_for_line(std::move(fr));
			}
#line 2680 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 130: /* todownto: toSYM  */
#line 741 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=toSYM;
			}
#line 2688 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 131: /* todownto: downtoSYM  */
#line 745 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=downtoSYM;
			}
#line 2696 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 132: /* optstep: stepSYM numexp  */
#line 751 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=(yyvsp[0].exp);
			}
#line 2704 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 133: /* optstep: %empty  */
#line 755 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=NULL;
			}
#line 2712 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 134: /* func_stat: funcSYM id procfunc_head optclosed opt_external  */
#line 761 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				comal::ProcFuncRec pf;
				pf.id       = (yyvsp[-3].id);
				pf.parmroot = comal::convert_parm_list(PARS_REVERSE(struct parm_list, (yyvsp[-2].parmptr)));
				pf.closed   = (yyvsp[-1].inum);
				pf.external = comal::convert_ext_rec((yyvsp[0].extptr));
				(yyval.pcl_modern) = (void*)comal::build_func_line(std::move(pf));
			}
#line 2725 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 135: /* if_stat: ifSYM numexp optthen optsimple_stat  */
#line 772 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_if_line(
					comal::IfWhileRec{comal::convert_expression((yyvsp[-2].exp)), (comal::ComalLine*)(yyvsp[0].pcl_modern)});
			}
#line 2734 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 136: /* import_stat: importSYM id colonSYM import_list  */
#line 779 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				comal::ImportRec ir;
				ir.id         = (yyvsp[-2].id);
				ir.importroot = comal::convert_import_list(PARS_REVERSE(struct import_list, (yyvsp[0].importptr)));
				(yyval.pcl_modern) = (void*)comal::build_import_line(std::move(ir));
			}
#line 2745 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 137: /* import_stat: importSYM import_list  */
#line 786 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				comal::ImportRec ir;
				ir.id         = nullptr;
				ir.importroot = comal::convert_import_list(PARS_REVERSE(struct import_list, (yyvsp[0].importptr)));
				(yyval.pcl_modern) = (void*)comal::build_import_line(std::move(ir));
			}
#line 2756 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 138: /* import_list: import_list commaSYM oneparm  */
#line 795 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.importptr)=PARS_ALLOC(struct import_list);
				(yyval.importptr)->id=(yyvsp[0].oneparm).id;
				(yyval.importptr)->array=(yyvsp[0].oneparm).array;
				(yyval.importptr)->next=(yyvsp[-2].importptr);				
			}
#line 2767 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 139: /* import_list: oneparm  */
#line 802 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.importptr)=PARS_ALLOC(struct import_list);
				(yyval.importptr)->id=(yyvsp[0].oneparm).id;
				(yyval.importptr)->array=(yyvsp[0].oneparm).array;
				(yyval.importptr)->next=NULL;
			}
#line 2778 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 140: /* input_stat: inputSYM input_modifier lval_list  */
#line 811 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				comal::InputRec ir;
				if ((yyvsp[-1].imod) == nullptr) {
					ir.modifier = nullptr;
				} else if ((yyvsp[-1].imod)->type == fileSYM) {
					ir.modifier = new comal::InputModifier(fileSYM,
						comal::TwoExp{comal::convert_expression((yyvsp[-1].imod)->data.twoexp.exp1),
						              comal::convert_expression((yyvsp[-1].imod)->data.twoexp.exp2)});
				} else {
					ir.modifier = new comal::InputModifier(stringSYM, (yyvsp[-1].imod)->data.str);
				}
				ir.lvalroot = comal::convert_exp_list(PARS_REVERSE(struct exp_list, (yyvsp[0].expptr)));
				(yyval.pcl_modern) = (void*)comal::build_input_line(std::move(ir));
			}
#line 2797 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 141: /* input_modifier: io_designator  */
#line 828 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.imod)=PARS_ALLOC(struct input_modifier);
				(yyval.imod)->type=fileSYM;
				(yyval.imod)->data.twoexp=(yyvsp[0].twoexp);
			}
#line 2807 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 142: /* input_modifier: stringSYM colonSYM  */
#line 834 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.imod)=PARS_ALLOC(struct input_modifier);
				(yyval.imod)->type=stringSYM;
				(yyval.imod)->data.str=(yyvsp[-1].str);
			}
#line 2817 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 143: /* input_modifier: %empty  */
#line 840 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.imod)=NULL;
			}
#line 2825 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 144: /* open_stat: openSYM fileSYM numexp commaSYM stringexp commaSYM open_type  */
#line 846 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				comal::OpenRec orec;
				orec.type      = (yyvsp[0].openrec).type;
				orec.reclen    = comal::convert_expression((yyvsp[0].openrec).reclen);
				orec.read_only = (yyvsp[0].openrec).read_only;
				orec.filenum   = comal::convert_expression((yyvsp[-4].exp));
				orec.filename  = comal::convert_expression((yyvsp[-2].exp));
				(yyval.pcl_modern) = (void*)comal::build_open_line(std::move(orec));
			}
#line 2839 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 145: /* open_stat: openSYM queueSYM numexp commaSYM stringexp commaSYM queue_type  */
#line 856 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				comal::OpenRec orec;
				orec.type      = (yyvsp[0].openrec).type;
				orec.reclen    = nullptr;
				orec.read_only = 0;
				orec.filenum   = comal::convert_expression((yyvsp[-4].exp));
				orec.filename  = comal::convert_expression((yyvsp[-2].exp));
				(yyval.pcl_modern) = (void*)comal::build_open_line(std::move(orec));
			}
#line 2853 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 146: /* open_type: readSYM  */
#line 868 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.openrec).type=readSYM;
				(yyval.openrec).reclen=NULL;
				(yyval.openrec).read_only=0;
			}
#line 2863 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 147: /* open_type: writeSYM  */
#line 874 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.openrec).type=writeSYM;
				(yyval.openrec).reclen=NULL;
				(yyval.openrec).read_only=0;
			}
#line 2873 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 148: /* open_type: appendSYM  */
#line 880 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.openrec).type=appendSYM;
				(yyval.openrec).reclen=NULL;
				(yyval.openrec).read_only=0;
			}
#line 2883 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 149: /* open_type: randomSYM numexp optread_only  */
#line 886 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.openrec).type=randomSYM;
				(yyval.openrec).reclen=(yyvsp[-1].exp);
				(yyval.openrec).read_only=(yyvsp[0].inum);
			}
#line 2893 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 150: /* queue_type: readSYM  */
#line 894 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.openrec).type=qreadSYM;
				(yyval.openrec).reclen=NULL;
				(yyval.openrec).read_only=0;
			}
#line 2903 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 151: /* queue_type: writeSYM  */
#line 900 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.openrec).type=qwriteSYM;
				(yyval.openrec).reclen=NULL;
				(yyval.openrec).read_only=0;
			}
#line 2913 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 152: /* os_stat: osSYM stringexp  */
#line 908 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_single_exp_line(comal::StatementType::Os,
					comal::convert_expression((yyvsp[0].exp)));
			}
#line 2922 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 153: /* print_stat: printi  */
#line 915 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				comal::PrintRec pr;
				pr.modifier  = nullptr;
				pr.printroot = nullptr;
				pr.pr_sep    = 0;
				(yyval.pcl_modern) = (void*)comal::build_print_line(std::move(pr));
			}
#line 2934 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 154: /* print_stat: printi print_list optpr_sep  */
#line 923 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				comal::PrintRec pr;
				pr.modifier  = nullptr;
				pr.printroot = comal::convert_print_list(PARS_REVERSE(struct print_list, (yyvsp[-1].printptr)));
				pr.pr_sep    = (yyvsp[0].inum);
				(yyval.pcl_modern) = (void*)comal::build_print_line(std::move(pr));
			}
#line 2946 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 155: /* print_stat: printi usingSYM stringexp colonSYM prnum_list optpr_sep  */
#line 931 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				comal::PrintRec pr;
				pr.modifier  = new comal::PrintModifier(usingSYM, comal::convert_expression((yyvsp[-3].exp)));
				pr.printroot = comal::convert_print_list(PARS_REVERSE(struct print_list, (yyvsp[-1].printptr)));
				pr.pr_sep    = (yyvsp[0].inum);
				(yyval.pcl_modern) = (void*)comal::build_print_line(std::move(pr));
			}
#line 2958 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 156: /* print_stat: printi io_designator print_list  */
#line 939 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				comal::PrintRec pr;
				pr.modifier  = new comal::PrintModifier(fileSYM,
					comal::TwoExp{comal::convert_expression((yyvsp[-1].twoexp).exp1),
					              comal::convert_expression((yyvsp[-1].twoexp).exp2)});
				pr.printroot = comal::convert_print_list(PARS_REVERSE(struct print_list, (yyvsp[0].printptr)));
				pr.pr_sep    = 0;
				(yyval.pcl_modern) = (void*)comal::build_print_line(std::move(pr));
			}
#line 2972 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 159: /* prnum_list: prnum_list pr_sep numexp  */
#line 955 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.printptr)=pars_printlist_item((yyvsp[-1].inum),(yyvsp[0].exp),(yyvsp[-2].printptr));
			}
#line 2980 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 160: /* prnum_list: numexp  */
#line 959 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.printptr)=pars_printlist_item(0,(yyvsp[0].exp),NULL);
			}
#line 2988 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 161: /* print_list: print_list pr_sep exp  */
#line 965 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.printptr)=pars_printlist_item((yyvsp[-1].inum),(yyvsp[0].exp),(yyvsp[-2].printptr));
			}
#line 2996 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 162: /* print_list: exp  */
#line 969 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.printptr)=pars_printlist_item(0,(yyvsp[0].exp),NULL);
			}
#line 3004 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 163: /* pr_sep: commaSYM  */
#line 975 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=commaSYM;
			}
#line 3012 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 164: /* pr_sep: semicolonSYM  */
#line 979 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=semicolonSYM;
			}
#line 3020 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 166: /* optpr_sep: %empty  */
#line 986 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=0;
			}
#line 3028 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 167: /* proc_stat: procSYM idSYM procfunc_head optclosed opt_external  */
#line 992 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				comal::ProcFuncRec pf;
				pf.id       = (yyvsp[-3].id);
				pf.parmroot = comal::convert_parm_list(PARS_REVERSE(struct parm_list, (yyvsp[-2].parmptr)));
				pf.closed   = (yyvsp[-1].inum);
				pf.external = comal::convert_ext_rec((yyvsp[0].extptr));
				(yyval.pcl_modern) = (void*)comal::build_proc_line(std::move(pf));
			}
#line 3041 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 168: /* read_stat: readSYM optfile lval_list  */
#line 1003 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				comal::ReadRec rr;
				if ((yyvsp[-1].twoexpp)) {
					rr.modifier = new comal::TwoExp{
						comal::convert_expression((yyvsp[-1].twoexpp)->exp1),
						comal::convert_expression((yyvsp[-1].twoexpp)->exp2)};
				} else {
					rr.modifier = nullptr;
				}
				rr.lvalroot = comal::convert_exp_list(PARS_REVERSE(struct exp_list, (yyvsp[0].expptr)));
				(yyval.pcl_modern) = (void*)comal::build_read_line(std::move(rr));
			}
#line 3058 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 169: /* restore_stat: restoreSYM optid2  */
#line 1018 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_restore_line((yyvsp[0].id));
			}
#line 3066 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 170: /* return_stat: returnSYM optexp  */
#line 1024 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_single_exp_line(comal::StatementType::Return,
					comal::convert_expression((yyvsp[0].exp)));
			}
#line 3075 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 171: /* select_out_stat: select_outputSYM stringexp  */
#line 1031 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_single_exp_line(comal::StatementType::Select_Output,
					comal::convert_expression((yyvsp[0].exp)));
			}
#line 3084 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 172: /* select_in_stat: select_inputSYM stringexp  */
#line 1039 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_single_exp_line(comal::StatementType::Select_Input,
					comal::convert_expression((yyvsp[0].exp)));
			}
#line 3093 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 173: /* stop_stat: stopSYM optexp  */
#line 1046 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_single_exp_line(comal::StatementType::Stop,
					comal::convert_expression((yyvsp[0].exp)));
			}
#line 3102 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 174: /* stop_stat: stopSYM spawnSYM numexp  */
#line 1051 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_single_exp_line(comal::StatementType::StopSpawn,
					comal::convert_expression((yyvsp[0].exp)));
			}
#line 3111 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 175: /* sys_stat: sysSYM exp_list  */
#line 1058 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				/* SYS maps to StatementType::Os with an ExpList* payload */
				comal::ExpList* args = comal::convert_exp_list(PARS_REVERSE(struct exp_list, (yyvsp[0].expptr)));
				(yyval.pcl_modern) = (void*)new comal::ComalLine(nullptr, comal::StatementType::Os, args);
			}
#line 3121 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 176: /* until_stat: untilSYM numexp  */
#line 1066 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_single_exp_line(comal::StatementType::Until,
					comal::convert_expression((yyvsp[0].exp)));
			}
#line 3130 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 177: /* trap_stat: trapSYM escSYM plusorminus  */
#line 1073 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_trap_line(comal::TrapRec{(yyvsp[0].inum)});
			}
#line 3138 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 178: /* plusorminus: plusSYM  */
#line 1079 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=plusSYM;
			}
#line 3146 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 179: /* plusorminus: minusSYM  */
#line 1083 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=minusSYM;
			}
#line 3154 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 180: /* when_stat: whenSYM when_list  */
#line 1089 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_when_line(
					comal::convert_when_list(PARS_REVERSE(struct when_list, (yyvsp[0].whenptr))));
			}
#line 3163 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 183: /* when_numlist: when_numlist commaSYM when_numitem  */
#line 1100 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.whenptr)=(yyvsp[0].whenptr);
				(yyval.whenptr)->next=(yyvsp[-2].whenptr);
			}
#line 3172 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 185: /* when_numitem: relop numexp  */
#line 1108 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.whenptr)=pars_whenlist_item((yyvsp[-1].inum),(yyvsp[0].exp),NULL);
			}
#line 3180 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 186: /* when_numitem: numexp  */
#line 1112 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.whenptr)=pars_whenlist_item(eqlSYM,(yyvsp[0].exp),NULL);
			}
#line 3188 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 187: /* when_strlist: when_strlist commaSYM when_stritem  */
#line 1118 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.whenptr)=(yyvsp[0].whenptr);
				(yyval.whenptr)->next=(yyvsp[-2].whenptr);
			}
#line 3197 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 189: /* when_stritem: relop stringexp  */
#line 1126 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.whenptr)=pars_whenlist_item((yyvsp[-1].inum),(yyvsp[0].exp),NULL);
			}
#line 3205 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 190: /* when_stritem: stringexp  */
#line 1130 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.whenptr)=pars_whenlist_item(eqlSYM,(yyvsp[0].exp),NULL);
			}
#line 3213 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 191: /* when_stritem: inSYM stringexp  */
#line 1134 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.whenptr)=pars_whenlist_item(inSYM,(yyvsp[0].exp),NULL);
			}
#line 3221 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 192: /* relop: gtrSYM  */
#line 1140 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=gtrSYM;
			}
#line 3229 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 193: /* relop: lssSYM  */
#line 1144 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=lssSYM;
			}
#line 3237 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 194: /* relop: eqlSYM  */
#line 1148 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=eqlSYM;
			}
#line 3245 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 195: /* relop: neqSYM  */
#line 1152 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=neqSYM;
			}
#line 3253 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 196: /* relop: geqSYM  */
#line 1156 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=geqSYM;
			}
#line 3261 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 197: /* relop: leqSYM  */
#line 1160 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=leqSYM;
			}
#line 3269 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 198: /* while_stat: whileSYM numexp optdo optsimple_stat  */
#line 1166 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_while_line(
					comal::IfWhileRec{comal::convert_expression((yyvsp[-2].exp)), (comal::ComalLine*)(yyvsp[0].pcl_modern)});
			}
#line 3278 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 199: /* repeat_stat: repeatSYM simple_stat untilSYM numexp  */
#line 1173 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_repeat_line(
					comal::IfWhileRec{comal::convert_expression((yyvsp[0].exp)), (comal::ComalLine*)(yyvsp[-2].pcl_modern)});
			}
#line 3287 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 200: /* write_stat: writeSYM file_designator exp_list  */
#line 1180 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				comal::WriteRec wr;
				wr.twoexp  = comal::TwoExp{comal::convert_expression((yyvsp[-1].twoexp).exp1),
				                           comal::convert_expression((yyvsp[-1].twoexp).exp2)};
				wr.exproot = comal::convert_exp_list(PARS_REVERSE(struct exp_list, (yyvsp[0].expptr)));
				(yyval.pcl_modern) = (void*)comal::build_write_line(std::move(wr));
			}
#line 3299 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 201: /* assign_stat: assign_list  */
#line 1190 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_assign_line(
					comal::convert_assign_list(PARS_REVERSE(struct assign_list, (yyvsp[0].assignptr))));
			}
#line 3308 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 202: /* assign_list: assign_list semicolonSYM assign_item  */
#line 1197 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.assignptr)=(yyvsp[0].assignptr);
				(yyval.assignptr)->next=(yyvsp[-2].assignptr);
			}
#line 3317 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 203: /* assign_list: assign_item  */
#line 1202 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.assignptr)->next=NULL;
			}
#line 3325 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 204: /* assign_item: numlvalue nassign numexp  */
#line 1208 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.assignptr)=pars_assign_item((yyvsp[-1].inum),(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3333 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 205: /* assign_item: strlvalue sassign stringexp  */
#line 1212 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.assignptr)=pars_assign_item((yyvsp[-1].inum),(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3341 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 209: /* sassign: becplusSYM  */
#line 1223 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=becplusSYM;
			}
#line 3349 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 210: /* assign1: eqlSYM  */
#line 1229 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=becomesSYM;
			}
#line 3357 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 211: /* assign1: becomesSYM  */
#line 1233 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=becomesSYM;
			}
#line 3365 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 212: /* assign2: becplusSYM  */
#line 1239 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=becplusSYM;
			}
#line 3373 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 213: /* assign2: becminusSYM  */
#line 1243 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=becminusSYM;
			}
#line 3381 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 214: /* label_stat: idSYM colonSYM  */
#line 1249 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = (void*)comal::build_label_line((yyvsp[-1].id));
			}
#line 3389 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 215: /* xid: idSYM  */
#line 1255 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_id(idSYM,(yyvsp[0].id),NULL);
			}
#line 3397 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 216: /* xid: idSYM lparenSYM exp_list rparenSYM  */
#line 1259 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_id(idSYM,(yyvsp[-3].id),(yyvsp[-1].expptr));
			}
#line 3405 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 217: /* xid: idSYM lparenSYM opt_commalist rparenSYM  */
#line 1263 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_array(idSYM,(yyvsp[-3].id),T_ARRAY);
			}
#line 3413 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 220: /* numexp: numexp2  */
#line 1273 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_num((yyvsp[0].exp));
			}
#line 3421 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 221: /* numexp2: numexp2 eqlSYM numexp2  */
#line 1279 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(eqlSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3429 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 222: /* numexp2: numexp2 neqSYM numexp2  */
#line 1283 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(neqSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3437 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 223: /* numexp2: numexp2 lssSYM numexp2  */
#line 1287 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(lssSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3445 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 224: /* numexp2: numexp2 gtrSYM numexp2  */
#line 1291 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(gtrSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3453 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 225: /* numexp2: numexp2 leqSYM numexp2  */
#line 1295 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(leqSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3461 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 226: /* numexp2: numexp2 geqSYM numexp2  */
#line 1299 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(geqSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3469 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 227: /* numexp2: numexp2 andSYM numexp2  */
#line 1303 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(andSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3477 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 228: /* numexp2: numexp2 andthenSYM numexp2  */
#line 1307 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(andthenSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3485 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 229: /* numexp2: numexp2 orSYM numexp2  */
#line 1311 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(orSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3493 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 230: /* numexp2: numexp2 orthenSYM numexp2  */
#line 1315 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(orthenSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3501 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 231: /* numexp2: numexp2 eorSYM numexp2  */
#line 1319 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(eorSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3509 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 232: /* numexp2: numexp2 plusSYM numexp2  */
#line 1323 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(plusSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3517 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 233: /* numexp2: numexp2 minusSYM numexp2  */
#line 1327 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(minusSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3525 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 234: /* numexp2: numexp2 timesSYM numexp2  */
#line 1331 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(timesSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3533 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 235: /* numexp2: numexp2 divideSYM numexp2  */
#line 1335 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(divideSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3541 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 236: /* numexp2: numexp2 powerSYM numexp2  */
#line 1339 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(powerSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3549 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 237: /* numexp2: numexp2 divSYM numexp2  */
#line 1343 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(divSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3557 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 238: /* numexp2: numexp2 modSYM numexp2  */
#line 1347 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(modSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3565 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 239: /* numexp2: stringexp2 eqlSYM stringexp2  */
#line 1351 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(eqlSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3573 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 240: /* numexp2: stringexp2 neqSYM stringexp2  */
#line 1355 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(neqSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3581 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 241: /* numexp2: stringexp2 lssSYM stringexp2  */
#line 1359 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(lssSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3589 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 242: /* numexp2: stringexp2 gtrSYM stringexp2  */
#line 1363 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(gtrSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3597 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 243: /* numexp2: stringexp2 leqSYM stringexp2  */
#line 1367 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(leqSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3605 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 244: /* numexp2: stringexp2 geqSYM stringexp2  */
#line 1371 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(geqSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3613 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 245: /* numexp2: stringexp2 inSYM stringexp2  */
#line 1375 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(inSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3621 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 246: /* numexp2: minusSYM numexp2  */
#line 1379 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary(minusSYM,(yyvsp[0].exp));
			}
#line 3629 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 247: /* numexp2: plusSYM numexp2  */
#line 1383 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary(plusSYM,(yyvsp[0].exp));
			}
#line 3637 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 248: /* numexp2: intnumSYM  */
#line 1387 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_int((yyvsp[0].num));
			}
#line 3645 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 249: /* numexp2: floatnumSYM  */
#line 1391 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_float(&(yyvsp[0].dubbel));
			}
#line 3653 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 251: /* numexp2: tsrnSYM lparenSYM stringexp2 rparenSYM  */
#line 1396 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary((yyvsp[-3].inum),(yyvsp[-1].exp));
			}
#line 3661 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 252: /* numexp2: lenSYM lparenSYM stringexp2 rparenSYM  */
#line 1400 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary((yyvsp[-3].inum),(yyvsp[-1].exp));
			}
#line 3669 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 253: /* numexp2: lenSYM lparenSYM numexp2 rparenSYM  */
#line 1404 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary((yyvsp[-3].inum),(yyvsp[-1].exp));
			}
#line 3677 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 254: /* numexp2: tnrnSYM lparenSYM numexp2 rparenSYM  */
#line 1408 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary((yyvsp[-3].inum),(yyvsp[-1].exp));
			}
#line 3685 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 255: /* numexp2: rndSYM  */
#line 1412 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(_RND,NULL,NULL);
			}
#line 3693 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 256: /* numexp2: rndSYM lparenSYM numexp2 rparenSYM  */
#line 1416 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(_RND,NULL,(yyvsp[-1].exp));
			}
#line 3701 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 257: /* numexp2: rndSYM lparenSYM numexp2 commaSYM numexp2 rparenSYM  */
#line 1420 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(_RND,(yyvsp[-3].exp),(yyvsp[-1].exp));
			}
#line 3709 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 258: /* numexp2: rnSYM  */
#line 1424 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_const((yyvsp[0].inum));
			}
#line 3717 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 259: /* numexp2: sysSYM lparenSYM exp_list rparenSYM  */
#line 1428 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_sys(sysSYM,T_SYS,(yyvsp[-1].expptr));
			}
#line 3725 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 260: /* numexp2: lparenSYM numexp2 rparenSYM  */
#line 1432 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary(lparenSYM,(yyvsp[-1].exp));
			}
#line 3733 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 261: /* stringexp: stringexp2  */
#line 1438 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_str((yyvsp[0].exp));
			}
#line 3741 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 262: /* stringexp2: stringexp2 plusSYM string_factor  */
#line 1444 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(plusSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3749 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 264: /* stringexp2: stringexp2 timesSYM numexp2  */
#line 1449 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_binary(timesSYM,(yyvsp[-2].exp),(yyvsp[0].exp));
			}
#line 3757 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 266: /* opt_stringexp: %empty  */
#line 1456 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=NULL;
			}
#line 3765 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 268: /* string_factor: string_factor substr_spec  */
#line 1463 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_substr((yyvsp[-1].exp),&(yyvsp[0].twoexp));
			}
#line 3773 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 269: /* string_factor: tnrsSYM lparenSYM numexp2 rparenSYM  */
#line 1467 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary((yyvsp[-3].inum),(yyvsp[-1].exp));
			}
#line 3781 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 270: /* string_factor: tsrsSYM lparenSYM stringexp2 rparenSYM  */
#line 1471 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary((yyvsp[-3].inum),(yyvsp[-1].exp));
			}
#line 3789 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 271: /* string_factor: rsSYM  */
#line 1475 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_const((yyvsp[0].inum));
			}
#line 3797 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 272: /* string_factor: tonrsSYM opt_arg  */
#line 1479 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary((yyvsp[-1].inum),(yyvsp[0].exp));
			}
#line 3805 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 273: /* string_factor: stringSYM  */
#line 1483 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_string((yyvsp[0].str));
			}
#line 3813 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 274: /* string_factor: syssSYM lparenSYM exp_list rparenSYM  */
#line 1487 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_sys(syssSYM,T_SYSS,(yyvsp[-1].expptr));
			}
#line 3821 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 275: /* string_factor: tsrsnSYM lparenSYM exp_list rparenSYM  */
#line 1491 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
			(yyval.exp)=pars_exp_sys((yyvsp[-3].inum),T_SYSS,(yyvsp[-1].expptr));
			}
#line 3829 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 276: /* string_factor: lparenSYM stringexp2 rparenSYM  */
#line 1495 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_unary(lparenSYM,(yyvsp[-1].exp));
			}
#line 3837 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 277: /* opt_arg: lparenSYM numexp2 rparenSYM  */
#line 1501 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=(yyvsp[-1].exp);
			}
#line 3845 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 278: /* opt_arg: %empty  */
#line 1505 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=NULL;
			}
#line 3853 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 279: /* substr_spec: lparenSYM substr_spec2 rparenSYM  */
#line 1511 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp)=(yyvsp[-1].twoexp);
			}
#line 3861 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 280: /* substr_spec2: numexp colonSYM numexp  */
#line 1517 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp).exp1=(yyvsp[-2].exp);
				(yyval.twoexp).exp2=(yyvsp[0].exp);
			}
#line 3870 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 281: /* substr_spec2: colonSYM numexp  */
#line 1522 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp).exp1=NULL;
				(yyval.twoexp).exp2=(yyvsp[0].exp);
			}
#line 3879 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 282: /* substr_spec2: numexp colonSYM  */
#line 1527 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp).exp1=(yyvsp[-1].exp);
				(yyval.twoexp).exp2=NULL;
			}
#line 3888 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 283: /* substr_spec2: colonSYM numexp colonSYM  */
#line 1532 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp).exp1=(yyvsp[-1].exp);
				(yyval.twoexp).exp2=(yyvsp[-1].exp);
			}
#line 3897 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 285: /* optnumlvalue: %empty  */
#line 1540 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=NULL;
			}
#line 3905 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 287: /* optexp: %empty  */
#line 1547 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=NULL;
			}
#line 3913 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 289: /* optid: %empty  */
#line 1554 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.id)=NULL;
			}
#line 3921 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 291: /* optid2: %empty  */
#line 1561 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.id)=NULL;
			}
#line 3929 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 292: /* optfile: file_designator  */
#line 1567 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexpp)=PARS_ALLOC(struct two_exp);
				
				*((yyval.twoexpp))=(yyvsp[0].twoexp);
			}
#line 3939 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 293: /* optfile: %empty  */
#line 1573 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {	
				(yyval.twoexpp)=NULL;
			}
#line 3947 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 297: /* lval_list: lval_list commaSYM lvalue  */
#line 1584 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.expptr)=pars_explist_item((yyvsp[0].exp),(yyvsp[-2].expptr));
			}
#line 3955 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 298: /* lval_list: lvalue  */
#line 1588 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.expptr)=pars_explist_item((yyvsp[0].exp),NULL);
			}
#line 3963 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 301: /* numlvalue: numlvalue2  */
#line 1598 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				if (!exp_list_of_nums((yyvsp[0].exp)->e.expid.exproot))
					pars_error("Indices of numeric lvalue \"%s\" must be numerics",(yyvsp[0].exp)->e.expid.id->name);
			}
#line 3972 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 303: /* numlvalue2: intidSYM  */
#line 1606 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_id(intidSYM,(yyvsp[0].id),NULL);
			}
#line 3980 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 304: /* numlvalue2: intidSYM lparenSYM exp_list rparenSYM  */
#line 1610 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_id(intidSYM,(yyvsp[-3].id),(yyvsp[-1].expptr));
			}
#line 3988 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 305: /* numlvalue2: intidSYM lparenSYM opt_commalist rparenSYM  */
#line 1614 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_array(intidSYM,(yyvsp[-3].id),T_ARRAY);
			}
#line 3996 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 306: /* strlvalue: strlvalue2  */
#line 1620 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				if (!exp_list_of_nums((yyvsp[0].exp)->e.expsid.exproot))
					pars_error("Indices of string lvalue \"%s\" must be numerics",(yyvsp[0].exp)->e.expsid.id->name);
			}
#line 4005 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 307: /* strlvalue2: stringidSYM  */
#line 1627 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_sid((yyvsp[0].id),NULL,NULL);
			}
#line 4013 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 308: /* strlvalue2: stringidSYM lparenSYM exp_list rparenSYM  */
#line 1631 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_sid((yyvsp[-3].id),(yyvsp[-1].expptr),NULL);
			}
#line 4021 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 309: /* strlvalue2: stringidSYM substr_spec  */
#line 1635 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_sid((yyvsp[-1].id),NULL,&(yyvsp[0].twoexp));
			}
#line 4029 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 310: /* strlvalue2: stringidSYM lparenSYM exp_list rparenSYM substr_spec  */
#line 1639 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_sid((yyvsp[-4].id),(yyvsp[-2].expptr),&(yyvsp[0].twoexp));
			}
#line 4037 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 311: /* strlvalue2: stringidSYM lparenSYM opt_commalist rparenSYM  */
#line 1643 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.exp)=pars_exp_array(intidSYM,(yyvsp[-3].id),T_SARRAY);
			}
#line 4045 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 312: /* file_designator: fileSYM numexp colonSYM  */
#line 1649 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp).exp1=(yyvsp[-1].exp);
				(yyval.twoexp).exp2=NULL;
			}
#line 4054 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 313: /* file_designator: fileSYM numexp commaSYM numexp colonSYM  */
#line 1654 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp).exp1=(yyvsp[-3].exp);
				(yyval.twoexp).exp2=(yyvsp[-1].exp);
			}
#line 4063 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 314: /* io_designator: fileSYM numexp colonSYM  */
#line 1661 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp).exp1=(yyvsp[-1].exp);
				(yyval.twoexp).exp2=NULL;
			}
#line 4072 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 315: /* io_designator: fileSYM numexp commaSYM numexp colonSYM  */
#line 1666 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp).exp1=(yyvsp[-3].exp);
				(yyval.twoexp).exp2=(yyvsp[-1].exp);
			}
#line 4081 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 316: /* io_designator: queueSYM numexp colonSYM  */
#line 1671 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp).exp1=(yyvsp[-1].exp);
				(yyval.twoexp).exp2=NULL;
			}
#line 4090 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 317: /* io_designator: queueSYM numexp commaSYM numexp colonSYM  */
#line 1676 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.twoexp).exp1=(yyvsp[-3].exp);
				(yyval.twoexp).exp2=(yyvsp[-1].exp);
			}
#line 4099 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 318: /* opt_external: externalSYM stringexp  */
#line 1683 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.extptr)=PARS_ALLOC(struct ext_rec);
				
				(yyval.extptr)->dynamic=0;
				(yyval.extptr)->filename=(yyvsp[0].exp);
				(yyval.extptr)->seg=NULL;
			}
#line 4111 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 319: /* opt_external: dynamicSYM externalSYM stringexp  */
#line 1691 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.extptr)=PARS_ALLOC(struct ext_rec);
				
				(yyval.extptr)->dynamic=dynamicSYM;
				(yyval.extptr)->filename=(yyvsp[0].exp);
				(yyval.extptr)->seg=NULL;
			}
#line 4123 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 320: /* opt_external: staticSYM externalSYM stringexp  */
#line 1699 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.extptr)=PARS_ALLOC(struct ext_rec);
				
				(yyval.extptr)->dynamic=staticSYM;
				(yyval.extptr)->filename=(yyvsp[0].exp);
				(yyval.extptr)->seg=NULL;
			}
#line 4135 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 321: /* opt_external: %empty  */
#line 1707 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.extptr)=NULL;
			}
#line 4143 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 322: /* procfunc_head: lparenSYM parmlist rparenSYM  */
#line 1713 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=(yyvsp[-1].parmptr);
			}
#line 4151 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 323: /* procfunc_head: %empty  */
#line 1717 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=NULL;
			}
#line 4159 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 324: /* parmlist: parmlist commaSYM parmitem  */
#line 1723 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=(yyvsp[0].parmptr);
				(yyval.parmptr)->next=(yyvsp[-2].parmptr);
			}
#line 4168 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 325: /* parmlist: parmitem  */
#line 1728 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=(yyvsp[0].parmptr);
				(yyval.parmptr)->next=NULL;
			}
#line 4177 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 326: /* parmitem: oneparm  */
#line 1735 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=PARS_ALLOC(struct parm_list);
				(yyval.parmptr)->id=(yyvsp[0].oneparm).id;
				(yyval.parmptr)->array=(yyvsp[0].oneparm).array;
				(yyval.parmptr)->ref=0;
			}
#line 4188 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 327: /* parmitem: refSYM oneparm  */
#line 1742 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=PARS_ALLOC(struct parm_list);
				(yyval.parmptr)->id=(yyvsp[0].oneparm).id;
				(yyval.parmptr)->array=(yyvsp[0].oneparm).array;
				(yyval.parmptr)->ref=refSYM;
			}
#line 4199 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 328: /* parmitem: nameSYM id  */
#line 1749 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=PARS_ALLOC(struct parm_list);
				(yyval.parmptr)->id=(yyvsp[0].id);
				(yyval.parmptr)->array=0;
				(yyval.parmptr)->ref=nameSYM;
			}
#line 4210 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 329: /* parmitem: procSYM idSYM  */
#line 1756 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=PARS_ALLOC(struct parm_list);
				(yyval.parmptr)->id=(yyvsp[0].id);
				(yyval.parmptr)->array=0;
				(yyval.parmptr)->ref=procSYM;
			}
#line 4221 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 330: /* parmitem: funcSYM id  */
#line 1763 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.parmptr)=PARS_ALLOC(struct parm_list);
				(yyval.parmptr)->id=(yyvsp[0].id);
				(yyval.parmptr)->array=0;
				(yyval.parmptr)->ref=funcSYM;
			}
#line 4232 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 331: /* oneparm: id  */
#line 1772 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.oneparm).id=(yyvsp[0].id);
				(yyval.oneparm).array=0;
			}
#line 4241 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 332: /* oneparm: id lparenSYM opt_commalist rparenSYM  */
#line 1777 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.oneparm).id=(yyvsp[-3].id);
				(yyval.oneparm).array=1;
			}
#line 4250 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 339: /* exp_list: exp_list commaSYM exp  */
#line 1796 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.expptr)=pars_explist_item((yyvsp[0].exp),(yyvsp[-2].expptr));
				}
#line 4258 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 340: /* exp_list: exp  */
#line 1800 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.expptr)=pars_explist_item((yyvsp[0].exp),NULL);
			}
#line 4266 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 341: /* optsimple_stat: simple_stat  */
#line 1806 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				/* simple_stat is already a heap-allocated ComalLine* */
				(yyval.pcl_modern) = (yyvsp[0].pcl_modern);
			}
#line 4275 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 342: /* optsimple_stat: %empty  */
#line 1811 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.pcl_modern) = nullptr;
			}
#line 4283 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 349: /* optread_only: read_onlySYM  */
#line 1829 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=read_onlySYM;
			}
#line 4291 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 350: /* optread_only: %empty  */
#line 1833 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=0;
			}
#line 4299 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 351: /* optclosed: closedSYM  */
#line 1839 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=closedSYM;
			}
#line 4307 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;

  case 352: /* optclosed: %empty  */
#line 1843 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"
                        {
				(yyval.inum)=0;
			}
#line 4315 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"
    break;


#line 4319 "/home/pnand/Workspace/Scratch/OpenCOMAL/build-prof/libcomal-parser/parser.tab.cc"

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

#line 1848 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"


PRIVATE void p_error(const char *s)
	{
		pars_error((char *)s);
		yyclearin;
	}
	
