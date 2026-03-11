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

#ifndef YY_YY_HOME_PETER_WORKSPACE_OPENCOMAL_BUILD_LIBCOMAL_PARSER_PARSER_TAB_H_INCLUDED
# define YY_YY_HOME_PETER_WORKSPACE_OPENCOMAL_BUILD_LIBCOMAL_PARSER_PARSER_TAB_H_INCLUDED
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
    drawSYM = 277,                 /* drawSYM  */
    divideSYM = 278,               /* divideSYM  */
    divSYM = 279,                  /* divSYM  */
    doSYM = 280,                   /* doSYM  */
    downtoSYM = 281,               /* downtoSYM  */
    dynamicSYM = 282,              /* dynamicSYM  */
    editSYM = 283,                 /* editSYM  */
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
    envSYM = 295,                  /* envSYM  */
    enterSYM = 296,                /* enterSYM  */
    eolnSYM = 297,                 /* eolnSYM  */
    eorSYM = 298,                  /* eorSYM  */
    eqlSYM = 299,                  /* eqlSYM  */
    escSYM = 300,                  /* escSYM  */
    execSYM = 301,                 /* execSYM  */
    exitSYM = 302,                 /* exitSYM  */
    externalSYM = 303,             /* externalSYM  */
    fileSYM = 304,                 /* fileSYM  */
    forSYM = 305,                  /* forSYM  */
    funcSYM = 306,                 /* funcSYM  */
    geqSYM = 307,                  /* geqSYM  */
    gtrSYM = 308,                  /* gtrSYM  */
    handlerSYM = 309,              /* handlerSYM  */
    ifSYM = 310,                   /* ifSYM  */
    importSYM = 311,               /* importSYM  */
    inputSYM = 312,                /* inputSYM  */
    inSYM = 313,                   /* inSYM  */
    leqSYM = 314,                  /* leqSYM  */
    listSYM = 315,                 /* listSYM  */
    localSYM = 316,                /* localSYM  */
    loadSYM = 317,                 /* loadSYM  */
    loopSYM = 318,                 /* loopSYM  */
    lparenSYM = 319,               /* lparenSYM  */
    lssSYM = 320,                  /* lssSYM  */
    minusSYM = 321,                /* minusSYM  */
    mkdirSYM = 322,                /* mkdirSYM  */
    modSYM = 323,                  /* modSYM  */
    nameSYM = 324,                 /* nameSYM  */
    neqSYM = 325,                  /* neqSYM  */
    newSYM = 326,                  /* newSYM  */
    nullSYM = 327,                 /* nullSYM  */
    ofSYM = 328,                   /* ofSYM  */
    openSYM = 329,                 /* openSYM  */
    orSYM = 330,                   /* orSYM  */
    orthenSYM = 331,               /* orthenSYM  */
    osSYM = 332,                   /* osSYM  */
    otherwiseSYM = 333,            /* otherwiseSYM  */
    pageSYM = 334,                 /* pageSYM  */
    plusSYM = 335,                 /* plusSYM  */
    powerSYM = 336,                /* powerSYM  */
    printSYM = 337,                /* printSYM  */
    procSYM = 338,                 /* procSYM  */
    quitSYM = 339,                 /* quitSYM  */
    randomSYM = 340,               /* randomSYM  */
    readSYM = 341,                 /* readSYM  */
    read_onlySYM = 342,            /* read_onlySYM  */
    refSYM = 343,                  /* refSYM  */
    renumberSYM = 344,             /* renumberSYM  */
    repeatSYM = 345,               /* repeatSYM  */
    restoreSYM = 346,              /* restoreSYM  */
    retrySYM = 347,                /* retrySYM  */
    returnSYM = 348,               /* returnSYM  */
    rmdirSYM = 349,                /* rmdirSYM  */
    rndSYM = 350,                  /* rndSYM  */
    rparenSYM = 351,               /* rparenSYM  */
    runSYM = 352,                  /* runSYM  */
    saveSYM = 353,                 /* saveSYM  */
    scanSYM = 354,                 /* scanSYM  */
    select_inputSYM = 355,         /* select_inputSYM  */
    select_outputSYM = 356,        /* select_outputSYM  */
    semicolonSYM = 357,            /* semicolonSYM  */
    staticSYM = 358,               /* staticSYM  */
    stepSYM = 359,                 /* stepSYM  */
    stopSYM = 360,                 /* stopSYM  */
    sysSYM = 361,                  /* sysSYM  */
    syssSYM = 362,                 /* syssSYM  */
    thenSYM = 363,                 /* thenSYM  */
    timesSYM = 364,                /* timesSYM  */
    toSYM = 365,                   /* toSYM  */
    traceSYM = 366,                /* traceSYM  */
    trapSYM = 367,                 /* trapSYM  */
    unitSYM = 368,                 /* unitSYM  */
    untilSYM = 369,                /* untilSYM  */
    usingSYM = 370,                /* usingSYM  */
    whenSYM = 371,                 /* whenSYM  */
    whileSYM = 372,                /* whileSYM  */
    writeSYM = 373,                /* writeSYM  */
    rnSYM = 374,                   /* rnSYM  */
    rsSYM = 375,                   /* rsSYM  */
    tnrnSYM = 376,                 /* tnrnSYM  */
    tnrsSYM = 377,                 /* tnrsSYM  */
    tsrnSYM = 378,                 /* tsrnSYM  */
    tonrsSYM = 379,                /* tonrsSYM  */
    tsrsSYM = 380,                 /* tsrsSYM  */
    tsrsnSYM = 381,                /* tsrsnSYM  */
    lenSYM = 382,                  /* lenSYM  */
    floatnumSYM = 383,             /* floatnumSYM  */
    idSYM = 384,                   /* idSYM  */
    intidSYM = 385,                /* intidSYM  */
    stringidSYM = 386,             /* stringidSYM  */
    intnumSYM = 387,               /* intnumSYM  */
    remSYM = 388,                  /* remSYM  */
    stringSYM = 389,               /* stringSYM  */
    USIGN = 390                    /* USIGN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 44 "/home/peter/Workspace/OpenCOMAL/libcomal-parser/src/parser.y"

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
	

#line 226 "/home/peter/Workspace/OpenCOMAL/build/libcomal-parser/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_HOME_PETER_WORKSPACE_OPENCOMAL_BUILD_LIBCOMAL_PARSER_PARSER_TAB_H_INCLUDED  */
