#ifndef __SOLVER_INTERFACE_H
#define __SOLVER_INTERFACE_H

#include <map>
#include <minizinc/ast.hh>
#include <minizinc/parser.hh>
#include <minizinc/model.hh>
namespace MiniZinc{
  class SolverInterface {
  public:
    SolverInterface();
    virtual ~SolverInterface();

    virtual void* getModel()=0;
    virtual void solve(SolveI* s) = 0;
    void addVar(VarDecl* vd);
    void postConstraint(ConstraintI& constraint);
    virtual void* resolveVar(SolverInterface&, Expression*)=0;
	
    void fromFlatZinc(MiniZinc::Model& m);
    void* lookupVar(VarDecl* vd);
    void* lookupVar(std::string s);
  protected:
    virtual void* addSolverVar(VarDecl*) = 0;
   

    typedef void (*poster) (SolverInterface&, const Call*);
    
    void addConstraintMapping(std::string mzn_constraint,
			      poster func);
    static std::pair<double,double> getFloatBounds(Expression* e){
      BinOp* bo = e->cast<BinOp>();
      double b, u;
      b = bo->_e0->cast<FloatLit>()->_v;
      u = bo->_e1->cast<FloatLit>()->_v;
      return std::pair<double,double>(b,u);
    }
    static std::pair<double,double> getIntBounds(Expression* e){
      BinOp* bo = e->cast<BinOp>();
      int b, u;
      b = bo->_e0->cast<IntLit>()->_v;
      u = bo->_e1->cast<IntLit>()->_v;
      return std::pair<int,int>(b,u);
    }
    poster lookupConstraint(std::string& s);
    std::map<VarDecl*, void*> variableMap;
    std::map<std::string, poster> constraintMap;
  };
};
#endif
