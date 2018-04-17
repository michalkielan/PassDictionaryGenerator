#include "OptionParser.hpp"


int main(int argc, char** argv)
{

  OptionParser parser{argc, argv};
  return parser.run();

}
