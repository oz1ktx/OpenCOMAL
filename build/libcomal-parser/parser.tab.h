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
    autoSYM = 261,                 /* autoSYM  */
    becomesSYM = 262,              /* becomesSYM  */
    becplusSYM = 263,              /* becplusSYM  */
    becminusSYM = 264,             /* becminusSYM  */
    caseSYM = 265,                 /* caseSYM  */
    chdirSYM = 266,                /* chdirSYM  */
    closedSYM = 267,               /* closedSYM  */
    closeSYM = 268,                /* closeSYM  */
    colonSYM = 269,                /* colonSYM  */
    commaSYM = 270,                /* commaSYM  */
    contSYM = 271,                 /* contSYM  */
    cursorSYM = 272,               /* cursorSYM  */
    dataSYM = 273,                 /* dataSYM  */
    delSYM = 274,                  /* delSYM  */
    dimSYM = 275,                  /* dimSYM  */
    dirSYM = 276,                  /* dirSYM  */
    divideSYM = 277,               /* divideSYM  */
    divSYM = 278,                  /* divSYM  */
    doSYM = 279,                   /* doSYM  */
    downtoSYM = 280,               /* downtoSYM  */
    dynamicSYM = 281,              /* dynamicSYM  */
    editSYM = 282,                 /* editSYM  */
    elifSYM = 283,                 /* elifSYM  */
    elseSYM = 284,                 /* elseSYM  */
    endcaseSYM = 285,              /* endcaseSYM  */
    endforSYM = 286,               /* endforSYM  */
    endfuncSYM = 287,              /* endfuncSYM  */
    endifSYM = 288,                /* endifSYM  */
    endloopSYM = 289,              /* endloopSYM  */
    endprocSYM = 290,              /* endprocSYM  */
    endSYM = 291,                  /* endSYM  */
    endtrapSYM = 292,              /* endtrapSYM  */
    endwhileSYM = 293,             /* endwhileSYM  */
    envSYM = 294,                  /* envSYM  */
    enterSYM = 295,                /* enterSYM  */
    eolnSYM = 296,                 /* eolnSYM  */
    eorSYM = 297,                  /* eorSYM  */
    eqlSYM = 298,                  /* eqlSYM  */
    escSYM = 299,                  /* escSYM  */
    execSYM = 300,                 /* execSYM  */
    exitSYM = 301,                 /* exitSYM  */
    externalSYM = 302,             /* externalSYM  */
    fileSYM = 303,                 /* fileSYM  */
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
    listSYM = 314,                 /* listSYM  */
    localSYM = 315,                /* localSYM  */
    loadSYM = 316,                 /* loadSYM  */
    loopSYM = 317,                 /* loopSYM  */
    lparenSYM = 318,               /* lparenSYM  */
    lssSYM = 319,                  /* lssSYM  */
    minusSYM = 320,                /* minusSYM  */
    mkdirSYM = 321,                /* mkdirSYM  */
    modSYM = 322,                  /* modSYM  */
    nameSYM = 323,                 /* nameSYM  */
    neqSYM = 324,                  /* neqSYM  */
    newSYM = 325,                  /* newSYM  */
    nullSYM = 326,                 /* nullSYM  */
    ofSYM = 327,                   /* ofSYM  */
    openSYM = 328,                 /* openSYM  */
    orSYM = 329,                   /* orSYM  */
    orthenSYM = 330,               /* orthenSYM  */
    osSYM = 331,                   /* osSYM  */
    otherwiseSYM = 332,            /* otherwiseSYM  */
    pageSYM = 333,                 /* pageSYM  */
    plusSYM = 334,                 /* plusSYM  */
    powerSYM = 335,                /* powerSYM  */
    printSYM = 336,                /* printSYM  */
    procSYM = 337,                 /* procSYM  */
    quitSYM = 338,                 /* quitSYM  */
    randomSYM = 339,               /* randomSYM  */
    readSYM = 340,                 /* readSYM  */
    read_onlySYM = 341,            /* read_onlySYM  */
    refSYM = 342,                  /* refSYM  */
    renumberSYM = 343,             /* renumberSYM  */
    repeatSYM = 344,               /* repeatSYM  */
    restoreSYM = 345,              /* restoreSYM  */
    retrySYM = 346,                /* retrySYM  */
    returnSYM = 347,               /* returnSYM  */
    rmdirSYM = 348,                /* rmdirSYM  */
    rndSYM = 349,                  /* rndSYM  */
    rparenSYM = 350,               /* rparenSYM  */
    runSYM = 351,                  /* runSYM  */
    saveSYM = 352,                 /* saveSYM  */
    scanSYM = 353,                 /* scanSYM  */
    select_inputSYM = 354,         /* select_inputSYM  */
    select_outputSYM = 355,        /* select_outputSYM  */
    semicolonSYM = 356,            /* semicolonSYM  */
    staticSYM = 357,               /* staticSYM  */
    stepSYM = 358,                 /* stepSYM  */
    stopSYM = 359,                 /* stopSYM  */
    sysSYM = 360,                  /* sysSYM  */
    syssSYM = 361,                 /* syssSYM  */
    thenSYM = 362,                 /* thenSYM  */
    timesSYM = 363,                /* timesSYM  */
    toSYM = 364,                   /* toSYM  */
    traceSYM = 365,                /* traceSYM  */
    trapSYM = 366,                 /* trapSYM  */
    unitSYM = 367,                 /* unitSYM  */
    untilSYM = 368,                /* untilSYM  */
    usingSYM = 369,                /* usingSYM  */
    whenSYM = 370,                 /* whenSYM  */
    whileSYM = 371,                /* whileSYM  */
    writeSYM = 372,                /* writeSYM  */
    rnSYM = 373,                   /* rnSYM  */
    rsSYM = 374,                   /* rsSYM  */
    tnrnSYM = 375,                 /* tnrnSYM  */
    tnrsSYM = 376,                 /* tnrsSYM  */
    tsrnSYM = 377,                 /* tsrnSYM  */
    tonrsSYM = 378,                /* tonrsSYM  */
    tsrsSYM = 379,                 /* tsrsSYM  */
    tsrsnSYM = 380,                /* tsrsnSYM  */
    floatnumSYM = 381,             /* floatnumSYM  */
    idSYM = 382,                   /* idSYM  */
    intidSYM = 383,                /* intidSYM  */
    stringidSYM = 384,             /* stringidSYM  */
    intnumSYM = 385,               /* intnumSYM  */
    remSYM = 386,                  /* remSYM  */
    stringSYM = 387,               /* stringSYM  */
    USIGN = 388                    /* USIGN  */
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
	

#line 224 "/home/pnand/Workspace/Scratch/OpenCOMAL/build/libcomal-parser/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_HOME_PNAND_WORKSPACE_SCRATCH_OPENCOMAL_BUILD_LIBCOMAL_PARSER_PARSER_TAB_H_INCLUDED  */
