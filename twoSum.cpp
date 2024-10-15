#include <iostream>
#include <vector>
#include <string>
#include <sstream>
class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        //Plan: check index 0 + all next indexes,
        //check index 1 + all next indexes, etc.
        //nums = [15, 7, 11, 2]
        //check 15+7 NO, check 15+11 NO, check 15+2 NO
        //check 7+11 NO, check 7+2 YES
        int total = 0;
        bool solutionFound = false;
        std::vector<int> indices;
        for(int i = 0; (i < (nums.size()-1)) && (solutionFound == false); i++) {
            for (int j = i+1; (j < nums.size()) && (solutionFound == false); j++) {
                total = nums[i]+nums[j];
                if (total == target) {
                    indices.push_back(i);
                    indices.push_back(j);
                    solutionFound = true;
                }
            }
        }
        if (solutionFound) {
            std::string vectorStr = vecToStr(nums);
            std::string targetStr = intToStr(target);
            std::string indicesStr = vecToStr(indices);
            std::string firstIndex = indicesStr.substr(1,1);
            std::string secondIndex = indicesStr.substr(3,1);
            std::cout << "Input: nums = " << vectorStr << ", target = " << targetStr << std::endl;
            std::cout << "Output: " << indicesStr << std::endl;
            std::cout << "Explanation: Because nums[" << firstIndex << "] + nums[" << secondIndex << "] == " <<
                targetStr << ", we return " << indicesStr << std::endl;
        } else {
            std::cout << "No solution found.";
        }
        return indices;
    }

    std::string vecToStr(std::vector<int>& nums) {
        std::stringstream ss;
        copy(nums.begin(), nums.end(), std::ostream_iterator<int>(ss,","));
        std::string str = ss.str();
        str = str.substr(0, str.length()-1); //Trimming trailing comma
        std::string finalStr = "[" + str + "]";
        return finalStr;
    }

    std::string intToStr(int& target) {
        std::stringstream ss;
        ss << target;
        std::string str = ss.str();
        return str;
    }
};

int main() {
    Solution solution;
    std::vector<int> nums;
    nums.push_back(2);
    nums.push_back(7);
    nums.push_back(11);
    nums.push_back(15);
    int target = 9;
    std::vector<int> indices = solution.twoSum(nums, target);
    return 0;
}