#include "CodeDumper.h"

CodeDumper::CodeDumper(): Debugger(){
  this->codeLineNum = 0;
}
void CodeDumper::debug(const std::string& message){
  if(this->m_debug){
      this->pfout->open(this->filename.c_str(), std::ofstream::app);
      *(this->pfout) << std::setfill('0') << std::setw(4) << codeLineNum << " " << message;
            codeLineNum++;
      this->pfout->close();
    }
}