#include "sLexer.h"
#include "sParser.h"


int main(int argc, char* argv[]){
	FILE * f = fopen("../villes-parse.csv", "w+");
  pANTLR3_INPUT_STREAM input;
  psLexer lex;
  pANTLR3_COMMON_TOKEN_STREAM tokens;
  psParser parser;

  input = antlr3AsciiFileStreamNew((pANTLR3_UINT8)argv[1]);
  lex = sLexerNew(input);
  tokens = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lex));
  parser = sParserNew(tokens);

  parser->s(parser,f);

  parser->free(parser);
  tokens->free(tokens);
  lex->free(lex);
  input->close(input);
  fclose(f);
  return 0;
}

