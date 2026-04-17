/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_HOME_PNAND_WORKSPACE_SCRATCH_OPENCOMAL_BUILD_LIBCOMAL_PARSER_PARSER_TAB_H_INCLUDED
# define YY_YY_HOME_PNAND_WORKSPACE_SCRATCH_OPENCOMAL_BUILD_LIBCOMAL_PARSER_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    andSYM = 258,                  /* andSYM  */
    andthenSYM = 259,              /* andthenSYM  */
    appendSYM = 260,               /* appendSYM  */
    becomesSYM = 261,              /* becomesSYM  */
    becplusSYM = 262,              /* becplusSYM  */
    becminusSYM = 263,             /* becminusSYM  */
    caseSYM = 264,                 /* caseSYM  */
    chdirSYM = 265,                /* chdirSYM  */
    closedSYM = 266,               /* closedSYM  */
    closeSYM = 267,                /* closeSYM  */
    colonSYM = 268,                /* colonSYM  */
    commaSYM = 269,                /* commaSYM  */
    cursorSYM = 270,               /* cursorSYM  */
    dataSYM = 271,                 /* dataSYM  */
    delSYM = 272,                  /* delSYM  */
    dimSYM = 273,                  /* dimSYM  */
    dirSYM = 274,                  /* dirSYM  */
    drawSYM = 275,                 /* drawSYM  */
    playSYM = 276,                 /* playSYM  */
    toneSYM = 277,                 /* toneSYM  */
    sleepSYM = 278,                /* sleepSYM  */
    divideSYM = 279,               /* divideSYM  */
    divSYM = 280,                  /* divSYM  */
    doSYM = 281,                   /* doSYM  */
    downtoSYM = 282,               /* downtoSYM  */
    dynamicSYM = 283,              /* dynamicSYM  */
    elifSYM = 284,                 /* elifSYM  */
    elseSYM = 285,                 /* elseSYM  */
    endcaseSYM = 286,              /* endcaseSYM  */
    endforSYM = 287,               /* endforSYM  */
    endfuncSYM = 288,              /* endfuncSYM  */
    endifSYM = 289,                /* endifSYM  */
    endloopSYM = 290,              /* endloopSYM  */
    endprocSYM = 291,              /* endprocSYM  */
    endSYM = 292,                  /* endSYM  */
    endtrapSYM = 293,              /* endtrapSYM  */
    endwhileSYM = 294,             /* endwhileSYM  */
    eolnSYM = 295,                 /* eolnSYM  */
    eorSYM = 296,                  /* eorSYM  */
    eqlSYM = 297,                  /* eqlSYM  */
    escSYM = 298,                  /* escSYM  */
    execSYM = 299,                 /* execSYM  */
    exitSYM = 300,                 /* exitSYM  */
    externalSYM = 301,             /* externalSYM  */
    fileSYM = 302,                 /* fileSYM  */
    queueSYM = 303,                /* queueSYM  */
    forSYM = 304,                  /* forSYM  */
    funcSYM = 305,                 /* funcSYM  */
    geqSYM = 306,                  /* geqSYM  */
    gtrSYM = 307,                  /* gtrSYM  */
    handlerSYM = 308,              /* handlerSYM  */
    ifSYM = 309,                   /* ifSYM  */
    importSYM = 310,               /* importSYM  */
    inputSYM = 311,                /* inputSYM  */
    inSYM = 312,                   /* inSYM  */
    leqSYM = 313,                  /* leqSYM  */
    localSYM = 314,                /* localSYM  */
    loopSYM = 315,                 /* loopSYM  */
    lparenSYM = 316,               /* lparenSYM  */
    lssSYM = 317,                  /* lssSYM  */
    minusSYM = 318,                /* minusSYM  */
    mkdirSYM = 319,                /* mkdirSYM  */
    modSYM = 320,                  /* modSYM  */
    nameSYM = 321,                 /* nameSYM  */
    neqSYM = 322,                  /* neqSYM  */
    nullSYM = 323,                 /* nullSYM  */
    ofSYM = 324,                   /* ofSYM  */
    openSYM = 325,                 /* openSYM  */
    orSYM = 326,                   /* orSYM  */
    orthenSYM = 327,               /* orthenSYM  */
    osSYM = 328,                   /* osSYM  */
    otherwiseSYM = 329,            /* otherwiseSYM  */
    pageSYM = 330,                 /* pageSYM  */
    plusSYM = 331,                 /* plusSYM  */
    powerSYM = 332,                /* powerSYM  */
    printSYM = 333,                /* printSYM  */
    procSYM = 334,                 /* procSYM  */
    randomSYM = 335,               /* randomSYM  */
    readSYM = 336,                 /* readSYM  */
    read_onlySYM = 337,            /* read_onlySYM  */
    refSYM = 338,                  /* refSYM  */
    repeatSYM = 339,               /* repeatSYM  */
    restoreSYM = 340,              /* restoreSYM  */
    retrySYM = 341,                /* retrySYM  */
    returnSYM = 342,               /* returnSYM  */
    rmdirSYM = 343,                /* rmdirSYM  */
    rndSYM = 344,                  /* rndSYM  */
    rparenSYM = 345,               /* rparenSYM  */
    select_inputSYM = 346,         /* select_inputSYM  */
    select_outputSYM = 347,        /* select_outputSYM  */
    semicolonSYM = 348,            /* semicolonSYM  */
    staticSYM = 349,               /* staticSYM  */
    stepSYM = 350,                 /* stepSYM  */
    stopSYM = 351,                 /* stopSYM  */
    spawnSYM = 352,                /* spawnSYM  */
    sysSYM = 353,                  /* sysSYM  */
    syssSYM = 354,                 /* syssSYM  */
    thenSYM = 355,                 /* thenSYM  */
    timesSYM = 356,                /* timesSYM  */
    toSYM = 357,                   /* toSYM  */
    trapSYM = 358,                 /* trapSYM  */
    unitSYM = 359,                 /* unitSYM  */
    untilSYM = 360,                /* untilSYM  */
    usingSYM = 361,                /* usingSYM  */
    whenSYM = 362,                 /* whenSYM  */
    whileSYM = 363,                /* whileSYM  */
    writeSYM = 364,                /* writeSYM  */
    qreadSYM = 365,                /* qreadSYM  */
    qwriteSYM = 366,               /* qwriteSYM  */
    rnSYM = 367,                   /* rnSYM  */
    rsSYM = 368,                   /* rsSYM  */
    tnrnSYM = 369,                 /* tnrnSYM  */
    tnrsSYM = 370,                 /* tnrsSYM  */
    tsrnSYM = 371,                 /* tsrnSYM  */
    tonrsSYM = 372,                /* tonrsSYM  */
    tsrsSYM = 373,                 /* tsrsSYM  */
    tsrsnSYM = 374,                /* tsrsnSYM  */
    lenSYM = 375,                  /* lenSYM  */
    floatnumSYM = 376,             /* floatnumSYM  */
    idSYM = 377,                   /* idSYM  */
    intidSYM = 378,                /* intidSYM  */
    stringidSYM = 379,             /* stringidSYM  */
    intnumSYM = 380,               /* intnumSYM  */
    remSYM = 381,                  /* remSYM  */
    stringSYM = 382,               /* stringSYM  */
    USIGN = 383                    /* USIGN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 44 "/home/pnand/Workspace/Scratch/OpenCOMAL/libcomal-parser/src/parser.y"

		long num;
		int inum;
		struct string *str;
		struct id_rec *id;
		struct dubbel dubbel;
		struct expression *exp;
		struct { struct id_rec *id; int array; } oneparm;
		struct two_num twonum;
		struct two_exp twoexp;
		struct two_exp *twoexpp;
		struct comal_line cl;
		struct comal_line *pcl;
		struct exp_list *expptr;
		struct ext_rec *extptr;
		struct dim_list *dimptr;
		struct dim_ension *dimensionptr;
		struct parm_list *parmptr;
		struct print_list *printptr;
		struct import_list *importptr;
		struct input_modifier *imod;
		struct when_list *whenptr;
		struct assign_list *assignptr;
		struct open_rec openrec;
	

#line 219 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_HOME_PNAND_WORKSPACE_SCRATCH_OPENCOMAL_BUILD_LIBCOMAL_PARSER_PARSER_TAB_H_INCLUDED  */
