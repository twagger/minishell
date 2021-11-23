%token  WORD
%token  ASSIGNMENT_WORD
%token  RET_TO
%token  RET_FROM
%token  PIPE
%token  DLESS
%token  DGREAT 

%start pipe_sequence
%%
pipe_sequence	: simple_command 
				| pipe_sequence PIPE simple_command
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
cmd_prefix      : io_redirect
                | cmd_prefix io_redirect
				;
cmd_suffix		: io_redirect
				| cmd_suffix io_redirect
				| WORD
				| cmd_suffix WORD
				;
io_redirect		: io_file
				| io_here
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