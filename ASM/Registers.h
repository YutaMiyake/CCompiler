#ifndef __REGISTERS__H__
#define __REGISTERS__H__
#include <queue>
#include <string>
class Registers{
public:
  Registers();
  std::string getRegister();
  void freeRegister(std::string reg);
  std::string getTempReg();
  std::string getArgReg();
  std::string getSavedTempReg();

private:
  const std::string argRegs[4] = {"$a0","$a1","$a2","$a3"};
  const std::string tempRegs[10] = {"$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7","$t8","$t9"};
  const std::string savedTempRegs[8] = {"$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7"};
  std::queue<std::string> argPool, tempPool, savedTempPool;
};
#endif