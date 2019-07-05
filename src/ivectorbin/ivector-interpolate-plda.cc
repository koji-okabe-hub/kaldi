// ivectorbin/ivector-adapt-plda.cc

// Copyright 2013-2014  Daniel Povey

// See ../../COPYING for clarification regarding multiple authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
// THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED
// WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
// MERCHANTABLITY OR NON-INFRINGEMENT.
// See the Apache 2 License for the specific language governing permissions and
// limitations under the License.


#include "base/kaldi-common.h"
#include "util/common-utils.h"
#include "ivector/plda.h"


int main(int argc, char *argv[]) {
  using namespace kaldi;
  typedef kaldi::int32 int32;
  try {
    const char *usage =
        "Interpolate PLDA models\n"
        "\n"
        "Usage: ivector-interpolate-plda [options] <plda-in1> <plda-in2> <plda-out>\n"
        "e.g.: ivector-interpolate-plda plda.ind plda.ood plda.adapted\n";

    ParseOptions po(usage);

    bool binary = true;
    double weight_between = 0.5;
    double weight_within  = 0.5;
    po.Register("binary", &binary, "Write output in binary mode");
    po.Register("weight_b", &weight_between, "weight of between-class covariance for plda-in1");
    po.Register("weight_w", &weight_within, "weight of within-class covariance for plda-in1");



    po.Read(argc, argv);

    if (po.NumArgs() != 3) {
      po.PrintUsage();
      exit(1);
    }

    std::string plda1_rxfilename = po.GetArg(1),
        plda2_rxfilename = po.GetArg(2),
        plda_wxfilename = po.GetArg(3);

    Plda plda1, plda2;
    ReadKaldiObject(plda1_rxfilename, &plda1);
    ReadKaldiObject(plda2_rxfilename, &plda2);

    plda1.Interpolation(&plda2, weight_between, weight_within);

    WriteKaldiObject(plda1, plda_wxfilename, binary);

    return 0;
  } catch(const std::exception &e) {
    std::cerr << e.what();
    return -1;
  }
}
