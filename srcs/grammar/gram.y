%token  WORD
%token  ASSIGNMENT_WORD
%token  RET_TO
%token  RET_FROM
%token  PIPE
%token  NEWLINE
%token  IO_NUMBER
%token  AND_IF
%token  OR_IF
%token  DLESS
%token  DGREAT 

%start and_or
%%
and_or			: pipe_sequence
				| and_or AND_IF linebreak pipe_sequence
				| and_or OR_IF linebreak pipe_sequence
				;
pipe_sequence	: simple_command 
				| pipe_sequence PIPE linebreak simple_command
				;
simple_command	: cmd_prefix cmd_word cmd_suffix
				| cmd_prefix cmd_word
				| cmd_prefix
				| cmd_name cmd_suffix
				| cmd_name
				;
cmd_name		: WORD
				;
cmd_word		: WORD
				;
cmd_prefix		: io_redirect
				| cmd_prefix io_redirect
				| ASSIGNMENT_WORD
				| cmd_prefix ASSIGNMENT_WORD
				;
cmd_suffix		: io_redirect
				| cmd_suffix io_redirect
				| WORD
				| cmd_suffix WORD
				;
io_redirect		: io_file
				| IO_NUMBER io_file
				| io_here
				| IO_NUMBER io_here
				;
io_file			: RET_TO filename
				| RET_FROM filename
				| DGREAT filename
				;
filename		: WORD
				;
io_here			: DLESS here_end
				;
here_end		: WORD
				;
newline_list	: NEWLINE
				| newline_list NEWLINE
				;
linebreak		: newline_list
				| /* empty */
				;