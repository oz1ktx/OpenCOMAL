#include "comal_parser_api.h"
#include "lexer_support.h"
#include "parser_support.h"
#include "comal_memory.h"
#include "comal_id.h"

#include <string.h>

extern struct comal_line c_line;

int comal_parse_line(const char *line, struct comal_line *out_line,
			     char *errbuf, size_t errbuf_len, int *errpos)
{
	int parse_rc;
	int error_pos;

	if (line == NULL) {
		if (errbuf && errbuf_len > 0) {
			strncpy(errbuf, "No input", errbuf_len - 1);
			errbuf[errbuf_len - 1] = '\0';
		}
		if (errpos) {
			*errpos = 0;
		}
		return 0;
	}

	lex_setinput((char *)line);
	parse_rc = yyparse();
	(void)parse_rc;

	error_pos = pars_handle_error_silent();
	if (error_pos) {
		if (errbuf && errbuf_len > 0) {
			const char *msg = pars_last_error();
			if (msg == NULL || msg[0] == '\0') {
				msg = "Parse error";
			}
			strncpy(errbuf, msg, errbuf_len - 1);
			errbuf[errbuf_len - 1] = '\0';
		}
		if (errpos) {
			*errpos = error_pos;
		}
		return 0;
	}

	if (out_line) {
		*out_line = c_line;
	}
	if (errbuf && errbuf_len > 0) {
		errbuf[0] = '\0';
	}
	if (errpos) {
		*errpos = 0;
	}

	return 1;
}

void comal_parser_reset(void)
{
	id_reset();
	mem_freepool(PARSE_POOL);
}

// ============================================================================
// Modern C++ API
// ============================================================================

namespace comal {

ComalLine* comal_parse_line_modern(const char *line,
                                   char *errbuf, size_t errbuf_len,
                                   int *errpos)
{
    struct comal_line legacy_line;
    memset(&legacy_line, 0, sizeof(legacy_line));

    if (!comal_parse_line(line, &legacy_line, errbuf, errbuf_len, errpos)) {
        return nullptr;
    }

    return convert_comal_line(&legacy_line);
}

const char* statement_type_name(StatementType cmd) {
    switch (cmd) {
        case StatementType::Empty:         return "EMPTY";
        case StatementType::Assign:        return "ASSIGN";
        case StatementType::Print:         return "PRINT";
        case StatementType::Input:         return "INPUT";
        case StatementType::Open:          return "OPEN";
        case StatementType::Close:         return "CLOSE";
        case StatementType::Read:          return "READ";
        case StatementType::Write:         return "WRITE";
        case StatementType::Dim:           return "DIM";
        case StatementType::Data:          return "DATA";
        case StatementType::Restore:       return "RESTORE";
        case StatementType::Exec:          return "EXEC";
        case StatementType::Return:        return "RETURN";
        case StatementType::Stop:          return "STOP";
        case StatementType::End:           return "END";
        case StatementType::Exit:          return "EXIT";
        case StatementType::Null:          return "NULL";
        case StatementType::Run:           return "RUN";
        case StatementType::Del:           return "DEL";
        case StatementType::Page:          return "PAGE";
        case StatementType::Cursor:        return "CURSOR";
        case StatementType::Select_Output: return "SELECT OUTPUT";
        case StatementType::Select_Input:  return "SELECT INPUT";
        case StatementType::Dir:           return "DIR";
        case StatementType::Unit:          return "UNIT";
        case StatementType::Chdir:         return "CHDIR";
        case StatementType::Mkdir:         return "MKDIR";
        case StatementType::Rmdir:         return "RMDIR";
        case StatementType::Os:            return "OS";
        case StatementType::Retry:         return "RETRY";
        case StatementType::Label:         return "LABEL";
        case StatementType::Local:         return "LOCAL";
        case StatementType::For:           return "FOR";
        case StatementType::If:            return "IF";
        case StatementType::Elif:          return "ELIF";
        case StatementType::Else:          return "ELSE";
        case StatementType::While:         return "WHILE";
        case StatementType::Repeat:        return "REPEAT";
        case StatementType::Until:         return "UNTIL";
        case StatementType::Loop:          return "LOOP";
        case StatementType::Case:          return "CASE";
        case StatementType::When:          return "WHEN";
        case StatementType::Otherwise:     return "OTHERWISE";
        case StatementType::Trap:          return "TRAP";
        case StatementType::Handler:       return "HANDLER";
        case StatementType::Proc:          return "PROC";
        case StatementType::Func:          return "FUNC";
        case StatementType::Import:        return "IMPORT";
        case StatementType::EndFor:        return "ENDFOR";
        case StatementType::EndIf:         return "ENDIF";
        case StatementType::EndWhile:      return "ENDWHILE";
        case StatementType::EndLoop:       return "ENDLOOP";
        case StatementType::EndCase:       return "ENDCASE";
        case StatementType::EndProc:       return "ENDPROC";
        case StatementType::EndFunc:       return "ENDFUNC";
        case StatementType::EndTrap:       return "ENDTRAP";
        case StatementType::List:          return "LIST";
        case StatementType::Save:          return "SAVE";
        case StatementType::Load:          return "LOAD";
        case StatementType::Enter:         return "ENTER";
        case StatementType::New:           return "NEW";
        case StatementType::Scan:          return "SCAN";
        case StatementType::Auto:          return "AUTO";
        case StatementType::Cont:          return "CONT";
        case StatementType::Edit:          return "EDIT";
        case StatementType::Renumber:      return "RENUMBER";
        case StatementType::Env:           return "ENV";
        case StatementType::Quit:          return "QUIT";
    }
    return "???";
}

} // namespace comal
