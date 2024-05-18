# pragma once
# include <iostream>
# include <fstream>
# include <cstring>
# include <vector>
# include <string>

# define _CRT_SECURE_NO_WARNINGS

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
            auto Buffer{ Tokens[pLine][Iterator] };
            std::cout << Buffer << ' ';
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


void PrintGreetings(LoggerParser& Object)
{
      std::cout << "LOGGER\n";
      for (size_t Iterator{}; Iterator < Object.Tokens.size(); ++Iterator)
      {
            Object.PrintTokensLine(Iterator);
      }
      std::cout << "\nPercent% of ERRORS'S - " << Object.fStatistic.ErrorAmount / float(Object.fStatistic.CommonAmount) << '\n';
      std::cout << "Percent% of WARNING'S - " << Object.fStatistic.WarningAmount / float(Object.fStatistic.CommonAmount) << '\n';
      std::cout << "Percent% of INFO'S - " << Object.fStatistic.InfoAmount / float(Object.fStatistic.CommonAmount) << '\n';

}