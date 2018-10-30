#pragma once
namespace geneticalgorithm {
	namespace fitness {
		enum FitnessOptimizationType { SINGLE_THREADED, PARALLEL_CPU };
	}
	namespace operators {
		namespace mutation {
			enum MutationOptimizationType { SINGLE_THREADED, PARALLEL_CPU };
		}
	}
}