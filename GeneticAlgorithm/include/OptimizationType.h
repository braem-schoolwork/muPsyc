#pragma once
namespace geneticalgorithm {
	namespace fitness {
		enum FitnessOptimizationType { SINGLE_THREADED, PARALLEL_CPU };
	}
	namespace operators {
		namespace selection {
			enum SelectionOptimizationType { SINGLE_THREADED, PARALLEL_CPU };
		}
		namespace mutation {
			enum MutationOptimizationType { SINGLE_THREADED, PARALLEL_CPU };
		}
		namespace crossover {
			enum CrossoverOptimizationType { SINGLE_THREADED, PARALLEL_CPU };
		}
	}
}