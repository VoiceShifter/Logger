# pragma once
# include <iostream>
# include <fstream>
# include <cstring>
# include <vector>
# include <string>

# define _CRT_SECURE_NO_WARNINGS

struct Colors
{
      const std::string RedColor{ "\033[0;31m" };
      const std::string YellowColor{ "\033[0;33m" };
      const std::string BlueColor{ "\033[0;36m" };
      const std::string Reset{ "\033[0m" };
} Colors;

enum class Items : size_t 
{
      Month,
      Date,
      Year,
      Time,
      Hostname,
      LoggingLevel,
      ApplicationLevelNProccess,
      Message
};


class LoggerParser
{
public:
      LoggerParser(char* pLogFile);
      ~LoggerParser();
      void AnalyzeLog();
      
      void PrintSpecificLevel(char);
      void PrintTokensLine(size_t pLine);
      std::vector<std::vector<std::string>> Tokens;
      friend void PrintGreetings(LoggerParser& Object);

private:
      std::fstream fLogFile;
      struct Statistic
      {
            size_t ErrorAmount;
            size_t WarningAmount;
            size_t InfoAmount;
            size_t CommonAmount;
      } fStatistic;
      
      void FillVector(std::vector<std::string>& pVector);
      //std::vector<std::string> fLines{};
};

LoggerParser::LoggerParser(char* pLogFile) : fStatistic{}
{
      fLogFile.open(pLogFile, std::ios::in);
      if (!fLogFile)
      {
            std::cout << "No such file\n";
            return;
      }
      AnalyzeLog();
}


LoggerParser::~LoggerParser()
{
      fLogFile.close();
}

void LoggerParser::FillVector(std::vector<std::string>& pVector)
{
      std::string Buffer{};
      for (size_t Iterator{}; std::getline(fLogFile, Buffer); ++Iterator)
      {
            pVector.push_back(Buffer);
      }
}

inline void LoggerParser::PrintTokensLine(size_t pLine)
{
      for (size_t Iterator{}; Iterator < Tokens[pLine].size(); ++Iterator)
      {
            if (Iterator == 5)
            {
                  switch (Tokens[pLine][Iterator][0])
                  {
                  case 69:
                        std::cout << Colors.RedColor;
                        break;
                  case 73:
                        std::cout << Colors.YellowColor;
                        break;
                  case 87:
                        std::cout << Colors.BlueColor;
                        break;

                  default:
                        break;
                  }                  
            }
            std::cout << Tokens[pLine][Iterator] << ' ' << Colors.Reset;
      }
      std::cout << '\n';
}

void LoggerParser::AnalyzeLog()
{
      std::vector<std::string> Lines{};
      FillVector(Lines);      

      Tokens.resize(Lines.size());

      for (size_t Iterator{}; Iterator < Lines.size(); ++Iterator)
      {            
            char* Token{ std::strtok(const_cast<char*>(Lines[Iterator].c_str()), " ") };            

            for (; Token != nullptr;)
            {
                  Tokens[Iterator].push_back(Token);
                  //std::cout << Token << " ";                  
                  Token = std::strtok(nullptr, " ");                  
            }
            ++this->fStatistic.CommonAmount;
            switch (Tokens[Iterator][static_cast<size_t>(Items::LoggingLevel)][0])
            {
            case 69:
                  ++this->fStatistic.ErrorAmount;
                  break;

            case 87:
                  ++this->fStatistic.WarningAmount;
                  break;

            case 73:
                  ++this->fStatistic.InfoAmount;
                  break;

            default:
                  std::cout << "Not mentioned log level found\n";
                  break;
            }
            //std::cout << '\n';
      }      
      
}

inline void LoggerParser::PrintSpecificLevel(char pLevel)
{
      for (size_t Iterator{}; Iterator < Tokens.size(); ++Iterator)
      {
            if (Tokens[Iterator][static_cast<size_t>(Items::LoggingLevel)][0] == pLevel)
            {
                  PrintTokensLine(Iterator);
            }
      }
}

void PrintOptions()
{
      std::cout << "Input: \n 1: To print only " << Colors.RedColor << "error's\n" << Colors.Reset;
      std::cout << " 2: To print only " << Colors.YellowColor << "warning's \n" << Colors.Reset;
      std::cout << " 3: To print only " << Colors.BlueColor << "info's\n" << Colors.Reset;
}

void PrintGreetings(LoggerParser& Object)
{
      signed int Choice{};

      std::cout << "LOGGER\n";
      for (size_t Iterator{}; Iterator < Object.Tokens.size(); ++Iterator)
      {
            Object.PrintTokensLine(Iterator);
      }
      std::cout << "\nPercent% of ERRORS'S - " << (Object.fStatistic.ErrorAmount / float(Object.fStatistic.CommonAmount))*100 << "%" << '\n';
      std::cout << "Percent% of WARNING'S - " << (Object.fStatistic.WarningAmount / float(Object.fStatistic.CommonAmount))*100 << "%" << '\n';
      std::cout << "Percent% of INFO'S - " << (Object.fStatistic.InfoAmount / float(Object.fStatistic.CommonAmount))*100 << "%" << '\n' << '\n'; 

      PrintOptions();
      std::cin >> Choice;
      std::cin.clear();
      switch (Choice)
      {
      case 1: 
            break;
      case 2:
            break;
      case 3:
            break;

      default:
            std::cout << "No such option\n";
            PrintOptions();
            break;
      }

}

