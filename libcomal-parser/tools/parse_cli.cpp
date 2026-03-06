#include "comal_parser_api.h"
#include "comal_ast_modern.h"
#include "comal_functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace comal;

// Map token IDs to readable operator strings
static const char* op_name(int op) {
	// Arithmetic
	if (op == 334) return "+";     // plusSYM
	if (op == 320) return "-";     // minusSYM
	if (op == 363) return "*";     // timesSYM
	if (op == 277) return "/";     // divideSYM
	if (op == 335) return "^";     // powerSYM
	if (op == 278) return "DIV";   // divSYM
	if (op == 322) return "MOD";   // modSYM
	// Comparison
	if (op == 298) return "=";     // eqlSYM
	if (op == 324) return "<>";    // neqSYM
	if (op == 319) return "<";     // lssSYM
	if (op == 313) return "<=";    // leqSYM
	if (op == 307) return ">";     // gtrSYM
	if (op == 306) return ">=";    // geqSYM
	// Logical
	if (op == 258) return "AND";   // andSYM
	if (op == 329) return "OR";    // orSYM
	if (op == 297) return "EOR";   // eorSYM
	if (op == 312) return "IN";    // inSYM
	// Assignment
	if (op == 262) return ":=";    // becomesSYM
	if (op == 263) return ":+";    // becplusSYM
	if (op == 264) return ":-";    // becminusSYM
	// Built-in functions (4000-4039)
	if (op == _ABS) return "ABS";
	if (op == _ACS) return "ACS";
	if (op == _ASN) return "ASN";
	if (op == _ATN) return "ATN";
	if (op == _CHR) return "CHR$";
	if (op == _COS) return "COS";
	if (op == _DEG) return "DEG";
	if (op == _EOD) return "EOD";
	if (op == _EOF) return "EOF";
	if (op == _EXP) return "EXP";
	if (op == _FALSE) return "FALSE";
	if (op == _TRUE) return "TRUE";
	if (op == _INT) return "INT";
	if (op == _LEN) return "LEN";
	if (op == _LN) return "LN";
	if (op == _LOG) return "LOG";
	if (op == _NOT) return "NOT";
	if (op == _ORD) return "ORD";
	if (op == _PI) return "PI";
	if (op == _RAD) return "RAD";
	if (op == _RND) return "RND";
	if (op == _SGN) return "SGN";
	if (op == _SIN) return "SIN";
	if (op == _SQR) return "SQR";
	if (op == _STR) return "STR$";
	if (op == _TAN) return "TAN";
	if (op == _VAL) return "VAL";
	if (op == _ERR) return "ERR";
	if (op == _ERRTEXT) return "ERRTEXT$";
	if (op == _ERRLINE) return "ERRLINE";
	if (op == _DIR) return "DIR$";
	if (op == _UNIT) return "UNIT";
	if (op == _SPC) return "SPC$";
	if (op == _KEY) return "KEY$";
	if (op == _INKEY) return "INKEY$";
	if (op == _UPPER) return "UPPER$";
	if (op == _LOWER) return "LOWER$";
	if (op == _FRAC) return "FRAC";
	if (op == _ROUND) return "ROUND";
	if (op == _SPLIT) return "SPLIT";
	// Parentheses (used for grouping)
	if (op == 318) return "";      // lparenSYM — grouping, no visible op
	// Fallback
	static char buf[16];
	snprintf(buf, sizeof(buf), "op%d", op);
	return buf;
}

// ============================================================================
// Expression pretty-printer (recursive)
// ============================================================================

static void print_expr(const Expression* expr, int depth) {
	if (!expr) {
		printf("(null)");
		return;
	}

	auto indent = [depth]() {
		for (int i = 0; i < depth; ++i) printf("  ");
	};

	switch (expr->opType()) {
	case OpType::IntNum:
		printf("%ld", (long)expr->asNum());
		break;
	case OpType::Float:
		printf("%g", expr->asFloat());
		break;
	case OpType::String:
		if (expr->asString())
			printf("\"%.*s\"", (int)expr->asString()->len, expr->asString()->s);
		else
			printf("\"\"");
		break;
	case OpType::Binary: {
		auto& te = expr->asTwoExp();
		if (expr->op() >= 4000) {
			// Built-in function call: e.g., RND, RND(x), RND(x,y)
			printf("%s", op_name(expr->op()));
			if (te.exp1 || te.exp2) {
				printf("(");
				if (te.exp1) print_expr(te.exp1, depth);
				if (te.exp1 && te.exp2) printf(", ");
				if (te.exp2) print_expr(te.exp2, depth);
				printf(")");
			}
		} else {
			printf("(");
			print_expr(te.exp1, depth);
			printf(" %s ", op_name(expr->op()));
			print_expr(te.exp2, depth);
			printf(")");
		}
		break;
	}
	case OpType::Unary:
		if (expr->op() >= 4000) {
			// Built-in unary function: e.g., ABS(x), NOT(x)
			printf("%s(", op_name(expr->op()));
			print_expr(expr->asExp(), depth);
			printf(")");
		} else {
			const char* name = op_name(expr->op());
			if (name[0] == '\0') {
				// lparenSYM — just grouping parens
				printf("(");
				print_expr(expr->asExp(), depth);
				printf(")");
			} else {
				printf("(%s ", name);
				print_expr(expr->asExp(), depth);
				printf(")");
			}
		}
		break;
	case OpType::Id: {
		auto& eid = std::get<ExpId>(expr->data());
		if (eid.id) printf("%s", eid.id->name);
		else printf("<id?>");
		if (eid.exproot) {
			printf("(");
			for (auto* n = eid.exproot; n; n = n->next()) {
				print_expr(n->exp(), depth);
				if (n->next()) printf(", ");
			}
			printf(")");
		}
		break;
	}
	case OpType::Sid: {
		auto& esid = std::get<ExpSid>(expr->data());
		if (esid.id) printf("%s", esid.id->name);
		else printf("<sid?>");
		if (esid.exproot) {
			printf("(");
			for (auto* n = esid.exproot; n; n = n->next()) {
				print_expr(n->exp(), depth);
				if (n->next()) printf(", ");
			}
			printf(")");
		}
		if (esid.twoexp) {
			printf("[");
			print_expr(esid.twoexp->exp1, depth);
			printf(":");
			print_expr(esid.twoexp->exp2, depth);
			printf("]");
		}
		break;
	}
	case OpType::Sys:
	case OpType::Syss: {
		// SYS/SYS$ store only an ExpList* (no id)
		printf(expr->opType() == OpType::Sys ? "SYS(" : "SYS$(");
		auto* el = std::get<ExpList*>(expr->data());
		for (auto* n = el; n; n = n->next()) {
			print_expr(n->exp(), depth);
			if (n->next()) printf(", ");
		}
		printf(")");
		break;
	}
	case OpType::Substr: {
		auto& es = std::get<ExpSubstr>(expr->data());
		print_expr(es.exp, depth);
		printf("(");
		print_expr(es.twoexp.exp1, depth);
		printf(":");
		print_expr(es.twoexp.exp2, depth);
		printf(")");
		break;
	}
	case OpType::Array:
	case OpType::Sarray: {
		auto& eid = std::get<ExpId>(expr->data());
		if (eid.id) printf("%s", eid.id->name);
		else printf("<arr?>");
		printf("()");
		break;
	}
	case OpType::Const:
	case OpType::ExpIsNum:
	case OpType::ExpIsString:
		// Wrapper types: just print the inner expression
		print_expr(expr->asExp(), depth);
		break;
	default:
		printf("<expr:%d>", (int)expr->opType());
		break;
	}
}

static void print_exp_list(const ExpList* list) {
	for (const ExpList* n = list; n; n = n->next()) {
		print_expr(n->exp(), 0);
		if (n->next()) printf(", ");
	}
}

// ============================================================================
// Modern AST pretty-printer for a single ComalLine
// ============================================================================

static void print_modern_line(const ComalLine* line) {
	printf("  %-14s", statement_type_name(line->command()));

	switch (line->command()) {
	case StatementType::For: {
		auto& f = line->asFor();
		printf("lval="); print_expr(f.lval, 0);
		printf(" from="); print_expr(f.from, 0);
		printf(" to="); print_expr(f.to, 0);
		if (f.step) { printf(" step="); print_expr(f.step, 0); }
		break;
	}
	case StatementType::If:
	case StatementType::While:
	case StatementType::Elif:
	case StatementType::Until:
	case StatementType::Repeat: {
		auto* rec = std::get_if<IfWhileRec>(&line->contents());
		if (rec && rec->exp) { printf("cond="); print_expr(rec->exp, 0); }
		break;
	}
	case StatementType::Print: {
		auto& pr = line->asPrint();
		if (pr.modifier) printf("[mod:%d] ", pr.modifier->type);
		for (auto* n = pr.printroot; n; n = n->next()) {
			print_expr(n->exp(), 0);
			if (n->separator()) printf(" sep:%d", n->separator());
			if (n->next()) printf("; ");
		}
		if (pr.pr_sep) printf(" trail-sep:%d", pr.pr_sep);
		break;
	}
	case StatementType::Input: {
		auto& ir = line->asInput();
		if (ir.modifier) printf("[mod:%d] ", ir.modifier->type);
		printf("lvals="); print_exp_list(ir.lvalroot);
		break;
	}
	case StatementType::Assign: {
		for (auto* n = line->asAssignList(); n; n = n->next()) {
			print_expr(n->lval(), 0);
			printf(" := ");
			print_expr(n->exp(), 0);
			if (n->next()) printf("; ");
		}
		break;
	}
	case StatementType::Exec:
	case StatementType::Case:
	case StatementType::Del:
	case StatementType::Chdir:
	case StatementType::Rmdir:
	case StatementType::Mkdir:
	case StatementType::Dir:
	case StatementType::Unit:
	case StatementType::Os:
	case StatementType::Return:
	case StatementType::Run:
	case StatementType::Stop:
	case StatementType::Select_Output:
	case StatementType::Select_Input:
	case StatementType::Exit: {
		auto* ep = std::get_if<Expression*>(&line->contents());
		if (ep && *ep) { printf("expr="); print_expr(*ep, 0); }
		break;
	}
	case StatementType::Proc:
	case StatementType::Func: {
		auto& pf = line->asProcFunc();
		if (pf.id) printf("id=%s", pf.id->name);
		if (pf.closed) printf(" CLOSED");
		if (pf.parmroot) {
			printf("(");
			for (auto* p = pf.parmroot; p; p = p->next()) {
				if (p->isRef()) printf("REF ");
				if (p->id()) printf("%s", p->id()->name);
				if (p->isArray()) printf("()");
				if (p->next()) printf(", ");
			}
			printf(")");
		}
		break;
	}
	case StatementType::Import: {
		auto& im = line->asImport();
		if (im.id) printf("module=%s ", im.id->name);
		for (auto* n = im.importroot; n; n = n->next()) {
			if (n->id()) printf("%s", n->id()->name);
			if (n->isArray()) printf("()");
			if (n->next()) printf(", ");
		}
		break;
	}
	case StatementType::Open: {
		auto& o = line->asOpen();
		printf("file#="); print_expr(o.filenum, 0);
		printf(" name="); print_expr(o.filename, 0);
		printf(" type=%d", o.type);
		if (o.read_only) printf(" RO");
		break;
	}
	case StatementType::Dim:
	case StatementType::Local: {
		auto* dl = std::get_if<DimList*>(&line->contents());
		if (dl) {
			for (auto* d = *dl; d; d = d->next()) {
				if (d->id()) printf("%s", d->id()->name);
				if (d->next()) printf(", ");
			}
		}
		break;
	}
	case StatementType::Data:
	case StatementType::Draw:
	case StatementType::Close: {
		auto* el = std::get_if<ExpList*>(&line->contents());
		if (el) print_exp_list(*el);
		break;
	}
	case StatementType::When: {
		for (auto* w = line->asWhenList(); w; w = w->next()) {
			printf("%s ", op_name(w->op()));
			print_expr(w->exp(), 0);
			if (w->next()) printf(", ");
		}
		break;
	}
	case StatementType::Read: {
		auto& r = line->asRead();
		if (r.modifier) printf("[file] ");
		printf("lvals="); print_exp_list(r.lvalroot);
		break;
	}
	case StatementType::Write: {
		auto& w = line->asWrite();
		printf("file=("); print_expr(w.twoexp.exp1, 0);
		printf(","); print_expr(w.twoexp.exp2, 0);
		printf(") data="); print_exp_list(w.exproot);
		break;
	}
	case StatementType::Trap: {
		auto& t = line->asTrap();
		if (t.esc) printf("ESC %d", t.esc);
		break;
	}
	case StatementType::Cursor: {
		auto& te = line->asTwoExp();
		printf("row="); print_expr(te.exp1, 0);
		printf(" col="); print_expr(te.exp2, 0);
		break;
	}
	case StatementType::List: {
		auto& lc = line->asList();
		if (lc.str) printf("file=%.*s ", (int)lc.str->len, lc.str->s);
		printf("range=%ld-%ld", (long)lc.twonum.num1, (long)lc.twonum.num2);
		if (lc.id) printf(" id=%s", lc.id->name);
		break;
	}
	case StatementType::Save:
	case StatementType::Load:
	case StatementType::Enter: {
		auto* sp = std::get_if<string*>(&line->contents());
		if (sp && *sp) printf("\"%.*s\"", (int)(*sp)->len, (*sp)->s);
		break;
	}
	case StatementType::Label:
	case StatementType::Restore:
	case StatementType::Env: {
		auto* ip = std::get_if<id_rec*>(&line->contents());
		if (ip && *ip) printf("%s", (*ip)->name);
		break;
	}
	case StatementType::Auto:
	case StatementType::Renumber:
	case StatementType::Edit: {
		auto& tn = line->asTwoNum();
		printf("%ld-%ld", (long)tn.num1, (long)tn.num2);
		break;
	}
	default:
		break;
	}

	printf("\n");
}

// ============================================================================
// Stream parsers
// ============================================================================

static int parse_stream_legacy(FILE *in, const char *label)
{
	char line[1024];
	unsigned long line_no = 0;
	int ok = 1;

	while (fgets(line, (int)sizeof(line), in) != NULL) {
		char errbuf[256];
		int errpos = 0;

		line_no++;

		if (!comal_parse_line(line, NULL, errbuf, sizeof(errbuf), &errpos)) {
			fprintf(stderr, "%s:%lu: parse error at %d: %s\n",
				label, line_no, errpos, errbuf[0] ? errbuf : "Parse error");
			ok = 0;
		}

		comal_parser_reset();
	}

	return ok;
}

static int parse_stream_modern(FILE *in, const char *label)
{
	char line[1024];
	unsigned long line_no = 0;
	int ok = 1;

	printf("=== Modern AST: %s ===\n", label);

	while (fgets(line, (int)sizeof(line), in) != NULL) {
		char errbuf[256];
		int errpos = 0;
		line_no++;

		// Strip trailing newline for cleaner display
		size_t len = strlen(line);
		if (len > 0 && line[len - 1] == '\n') line[len - 1] = '\0';

		ComalLine* modern = comal_parse_line_modern(line, errbuf,
		                                            sizeof(errbuf), &errpos);
		if (!modern) {
			fprintf(stderr, "%s:%lu: parse error at %d: %s\n",
				label, line_no, errpos, errbuf[0] ? errbuf : "Parse error");
			ok = 0;
		} else {
			printf("%3lu: ", line_no);
			print_modern_line(modern);
			delete modern;
		}

		comal_parser_reset();
	}

	printf("=== End ===\n");
	return ok;
}

// ============================================================================

int main(int argc, char **argv)
{
	int ok = 1;
	int modern = 0;

	// Check for -m flag
	int file_arg = -1;
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-m") == 0) {
			modern = 1;
		} else if (file_arg < 0) {
			file_arg = i;
		}
	}

	if (argc - modern > 2) {
		fprintf(stderr, "Usage: %s [-m] [file]\n", argv[0]);
		return 2;
	}

	auto parse_fn = modern ? parse_stream_modern : parse_stream_legacy;

	if (file_arg > 0) {
		FILE *in = fopen(argv[file_arg], "r");
		if (in == NULL) {
			perror("fopen");
			return 2;
		}
		ok = parse_fn(in, argv[file_arg]);
		fclose(in);
	} else {
		ok = parse_fn(stdin, "<stdin>");
	}

	return ok ? 0 : 1;
}
