/******************************************************************************
 * Copyright (c) 2017 Philipp Schubert.
 * All rights reserved. This program and the accompanying materials are made
 * available under the terms of LICENSE.txt.
 *
 * Contributors:
 *     Philipp Schubert and others
 *****************************************************************************/

/*
 * InterMonoProblem.h
 *
 *  Created on: 23.06.2017
 *      Author: philipp
 */

#ifndef PHASAR_PHASARLLVM_MONO_INTERMONOPROBLEM_H_
#define PHASAR_PHASARLLVM_MONO_INTERMONOPROBLEM_H_

#include <string>
#include <type_traits>

#include <phasar/Config/ContainerConfiguration.h>

namespace psr {

template <typename N, typename D, typename M, typename I>
class InterMonoProblem {
public:
  using Node_t = N;
  using Domain_t = D;
  using Method_t = M;
  using ICFG_t = I;

protected:
  ICFG_t &ICFG;

public:
  InterMonoProblem(ICFG_t &Icfg) : ICFG(Icfg) {}

  InterMonoProblem(const InterMonoProblem &copy) = delete;
  InterMonoProblem(InterMonoProblem &&move) = delete;
  InterMonoProblem &operator=(const InterMonoProblem &copy) = delete;
  InterMonoProblem &operator=(InterMonoProblem &&move) = delete;

  virtual ~InterMonoProblem() = default;
  ICFG_t &getICFG() noexcept { return ICFG; }
  virtual Domain_t join(const Domain_t &Lhs, const Domain_t &Rhs) = 0;
  virtual bool sqSubSetEqual(const Domain_t &Lhs, const Domain_t &Rhs) = 0;
  virtual Domain_t normalFlow(const Node_t Stmt, const Domain_t &In) = 0;
  virtual Domain_t callFlow(const Node_t CallSite, const Method_t Callee,
                            const Domain_t &In) = 0;
  virtual Domain_t returnFlow(const Node_t CallSite, const Method_t Callee,
                              const Node_t RetSite, const Domain_t &In) = 0;
  virtual Domain_t callToRetFlow(const Node_t CallSite, const Node_t RetSite,
                                 const Domain_t &In) = 0;
  virtual MonoMap<Node_t, Domain_t> initialSeeds() = 0;
  virtual std::string DtoString(const Domain_t d) = 0;
  virtual std::string MtoString(const Method_t m) = 0;
  virtual std::string NtoString(const Node_t n) = 0;
  virtual bool recompute(const Method_t Callee) = 0;
};

} // namespace psr

#endif
