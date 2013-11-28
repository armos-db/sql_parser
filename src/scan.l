%{
/**
 * Copyright (C) 2013 Louis Hust. All Rights Reserved.
 */

%}


%%

[a-zA-Z]+ { fprintf(stdout, "We get a word: %s.\n", yytext); }
\n { fprintf(stdout, "We get a \\n.\n"); }

%%
/* Utility functions */
