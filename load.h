#include <string>
#include <vector>
short** getMap(std::string filename, int szX, int szY);
std::vector<std::string> getDoors();
void loadSave(std::string saveFile, short* xy);