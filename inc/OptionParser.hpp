/**
 * @file OptionParser.hpp
 *
 * @brief
 *
 * @date Apr 17, 2018
 * @author Michal Kielan
 */

#ifndef SRC_OPTIONPARSER_HPP_
#define SRC_OPTIONPARSER_HPP_

#include <boost/program_options.hpp>

namespace po = boost::program_options;

class OptionParser
{
  po::variables_map       mVariableMap;
  po::options_description mDescription;

  const struct
  {
    const std::string help {"help"};
    const std::string words {"words"};
    const std::string characters {"characters"};
  } mParams;

  OptionParser(const int argc, char** argv);

  int run();

public:

  static int generateRandom(const int argc, char** argv)
  {
    OptionParser parser{argc, argv};
    return parser.run();
  }

};

#endif /* SRC_OPTIONPARSER_HPP_ */
