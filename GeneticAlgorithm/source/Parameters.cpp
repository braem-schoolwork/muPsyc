#include "Parameters.h"

using namespace std;

bool Parameters::SetOperatorCounts(double percentElites, double percentMutations, double percentCrossovers)
{
    double sum = percentElites + percentMutations + percentCrossovers;
    if (sum > 1.0 + numeric_limits<double>::epsilon() * 3.0 ||
        sum < 1.0 - numeric_limits<double>::epsilon() * 3.0)
    {
        return false;
    }
    m_iNumElites = static_cast<int>
        (round((percentElites / 100.0) * static_cast<double>(m_iPopulationSize)) + numeric_limits<double>().epsilon() * 4.0);
    m_iNumMutations = static_cast<int>
        (round((percentMutations / 100.0) * static_cast<double>(m_iPopulationSize)) + numeric_limits<double>().epsilon() * 4.0);
    m_iNumCrossovers = static_cast<int>
        (round((percentCrossovers / 100.0) * static_cast<double>(m_iPopulationSize)) + numeric_limits<double>().epsilon() * 4.0);
    return true;
}

void Parameters::SetElitismCount(double elitismPercent)
{
    m_iElitismCount = static_cast<int>(round((elitismPercent / 100.0) * static_cast<double>(m_iNumElites)) + numeric_limits<double>::epsilon() * 4.0);
}

ostream& operator<<(ostream& strm, const Parameters& params)
{
    strm << "Initial Composition Generation Parameters:" << endl;
    strm << params.m_InitParams << endl;
    strm << "Population Size: " << params.m_iPopulationSize << endl;
    strm << "Number of Elites: " << params.m_iNumElites << endl;
    strm << "Number of Mutations: " << params.m_iNumMutations << endl;
    strm << "Number of Crossovers: " << params.m_iNumCrossovers << endl;
    strm << "Number of Generations: " << params.m_iNumGenerations << endl;
    strm << "Using only Traditional Rules: " << params.m_bOnlyTraditionalRules << endl;
    strm << "Elitism Size: " << params.m_iElitismCount << endl;
    strm << "Fitness Threshold: " << params.m_dbThreshold << endl;
    strm << "Implement Aging: " << params.m_dbThreshold << endl;
    strm << "Selection Method: " << params.m_SelType << endl;
    if (params.m_SelType == SELECTION_TOURNAMENT_DETERMINISTIC)
        strm << "Tournament Size: " << params.m_iTournamentSize << endl;
    if (params.m_SelType == SELECTION_TOURNAMENT) {
        strm << "Tournament Size: " << params.m_iTournamentSize << endl;
        strm << "Tournament Selection Probability: " << params.m_dbTournamentProb << endl;
    }
    strm << "Fitness Scaling Method: " << params.m_FitnessScalingType << endl;
    if (params.m_FitnessScalingType == FITNESS_SCALING_POWER_LAW)
        strm << "Power Law Power: " << params.m_iPowerLawScalingPower << endl;
    strm << "Mutation Operator Probabilities: " << endl;
    strm << "\t Random Transposition: " << params.m_dbRandomTransposeProb << endl;
    strm << "\t Split: " << params.m_dbSplitProb << endl;
    strm << "\t Merge: " << params.m_dbMergeProb << endl;
    strm << "\t Repeat: " << params.m_dbRepeatProb << endl;
    strm << "Optimization: " << endl;
    strm << "\t Fitness Function: " << params.m_FitnessOptType << endl;
    strm << "\t Selection: " << params.m_SelOptType << endl;
    strm << "\t Mutation: " << params.m_MutOptType << endl;
    strm << "\t Crossover: " << params.m_CrossOptType << endl;
    strm << "Directory: " << params.m_StrMainOutputDir << endl;
    strm << "Number of Runs: " << params.m_iNumRuns << endl;
    return strm;
}

istream& operator>>(istream& strm, Parameters& params)
{
    string line, paramStr, delim = ":", secondaryDelim = ",";
    size_t pos, pos2;
    getline(strm, line); //initial comment. Not useful
    getline(strm, line); pos = line.find(delim); //comp name
    paramStr = line.substr(pos + 2, line.length()); params.m_InitParams.m_vecName = paramStr;
    getline(strm, line); pos = line.find(delim); //numParts
    paramStr = line.substr(pos + 2, line.length()); params.m_InitParams.m_iNumParts = stoi(paramStr);
    getline(strm, line); pos = line.find(delim); //numMeasures
    paramStr = line.substr(pos + 2, line.length()); params.m_InitParams.m_iNumMeasures = stoi(paramStr);
    getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //part names
    vector<string> partnames(params.m_InitParams.m_iNumParts);
    for (auto i = 0; i < params.m_InitParams.m_iNumParts; i++)
    {
        if (i == params.m_InitParams.m_iNumParts - 1)
        {
            partnames[i] = paramStr.substr(0, paramStr.length());
            break;
        }
        pos2 = paramStr.find_first_of(secondaryDelim);
        partnames[i] = paramStr.substr(0, pos2);
        paramStr = paramStr.substr(pos2 + 2, paramStr.length());
    }
    params.m_InitParams.m_vecPartNames = partnames;
    getline(strm, line); pos = line.find(delim); //key
    paramStr = line.substr(pos + 2, line.length()); params.m_InitParams.m_Key = Key(paramStr);
    getline(strm, line); pos = line.find(delim); //time sig
    paramStr = line.substr(pos + 2, line.length()); params.m_InitParams.m_TimeSig = TimeSignature(paramStr);
    getline(strm, line); pos = line.find(delim); //bpm
    paramStr = line.substr(pos + 2, line.length()); params.m_InitParams.m_BPM = BPM(paramStr);
    getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //midi instruments
    vector<char> instrs(params.m_InitParams.m_iNumParts);
    for (auto i = 0; i < params.m_InitParams.m_iNumParts; i++)
    {
        if (i == params.m_InitParams.m_iNumParts - 1)
        {
            instrs[i] = static_cast<char>(stoi(paramStr.substr(0, paramStr.length())));
            break;
        }
        pos2 = paramStr.find_first_of(secondaryDelim);
        instrs[i] = static_cast<char>(stoi(paramStr.substr(0, pos2)));
        paramStr = paramStr.substr(pos2 + 2, paramStr.length());
    }
    params.m_InitParams.m_vecInstruments = instrs;
    getline(strm, line); //bounds header
    vector<Pitch> lbnds(params.m_InitParams.m_iNumParts);
    vector<Pitch> ubnds(params.m_InitParams.m_iNumParts);
    for (auto i = 0; i < params.m_InitParams.m_iNumParts; i++)
    {
        getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //instrument bounds
        pos2 = paramStr.find(secondaryDelim);
        lbnds[i] = Pitch(paramStr.substr(0, pos2));
        pos = paramStr.find(delim);
        ubnds[i] = Pitch(paramStr.substr(pos + 2, paramStr.length()));
    }
    params.m_InitParams.m_vecLowerBounds = lbnds;
    params.m_InitParams.m_vecUpperBounds = ubnds;
    getline(strm, line); //chords header
    strm >> params.m_InitParams.m_ChordProgression;
    //DONE INITPARAMS
    getline(strm, line); //whitespace between both param objs
    getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //population size
    params.m_iPopulationSize = stoi(paramStr);
    getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //elites
    params.m_iNumElites = stoi(paramStr);
    getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //mutations
    params.m_iNumMutations = stoi(paramStr);
    getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //crossovers
    params.m_iNumCrossovers = stoi(paramStr);
    getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //num gens
    params.m_iNumGenerations = stoi(paramStr);
    getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //traditional rules bool
    params.m_bOnlyTraditionalRules = stoi(paramStr);
    getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //elitism count
    params.m_iElitismCount = stoi(paramStr);
    getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //threshold
    params.m_dbThreshold = stod(paramStr);
    getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //aging
    params.m_bUseAging = stoi(paramStr);
    getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //selection type
    params.m_SelType = GetSelectionTypeFromString(paramStr);
    if (params.m_SelType == SELECTION_TOURNAMENT_DETERMINISTIC)
    {
        getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //tourny size
        params.m_iTournamentSize = stoi(paramStr);
    }
    else if (params.m_SelType == SELECTION_TOURNAMENT)
    {
        getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //tourny size
        params.m_iTournamentSize = stoi(paramStr);
        getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //tourny prob
        params.m_dbTournamentProb = stod(paramStr);
    }
    getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //fitness scaling type
    params.m_FitnessScalingType = GetFitnessScalingTypeFromString(paramStr);
    if (params.m_FitnessScalingType == FITNESS_SCALING_POWER_LAW)
    {
        getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //power law power
        params.m_iPowerLawScalingPower = stoi(paramStr);
    }
    getline(strm, line); //mutation op probs header
    getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //mut op random transpose
    params.m_dbRandomTransposeProb = stod(paramStr);
    getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //mut op split
    params.m_dbSplitProb = stod(paramStr);
    getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //mut op merge
    params.m_dbMergeProb = stod(paramStr);
    getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //mut op repeat
    params.m_dbRepeatProb = stod(paramStr);
    getline(strm, line); //optimization header
    getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //selection type
    params.m_FitnessOptType = getFitnessOptimizationTypeFromString(paramStr);
    getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //selection type
    params.m_SelOptType = getSelectionOptimizationTypeFromString(paramStr);
    getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //selection type
    params.m_MutOptType = getMutationOptimizationTypeFromString(paramStr);
    getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //selection type
    params.m_CrossOptType = getCrossoverOptimizationTypeFromString(paramStr);
    getline(strm, line); pos = line.find(delim); //main directory
    paramStr = line.substr(pos + 2, line.length()); params.m_StrMainOutputDir = paramStr;
    getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //number of runs
    params.m_iNumRuns = stoi(paramStr);
    return strm;
}
