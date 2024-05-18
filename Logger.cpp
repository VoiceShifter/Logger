
#include "Logger.h"

signed int main(unsigned int argc, char **argv)
{
      if (argc > 2)
      {
            std::cout << "Too many arguments\n";
            return 0;
      }
      else
      {
            LoggerParser Parser(argv[1]);
            Parser.AnalyzeLog();
//          Parser.PrintTokensLine(1);

      }
      
}
