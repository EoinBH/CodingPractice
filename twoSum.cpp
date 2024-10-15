#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        //Plan: use a HashMap to store values of vector and their indices
        //Assuming x+y = target, when storing x, check if y already exists in HashMap
        int matchingVal = 0;
        bool solutionFound = false;
        std::vector<int> indices;
        std::unordered_map<int, int> hashMap; //HashMap<value, index>
        for(int i = 0; (i < nums.size()) && (solutionFound == false); i++) {
            if (nums[i] <= target) {
                matchingVal = target - nums[i];
                //Check if matching value already exists
                if (hashMap.find(matchingVal) == hashMap.end()) {
                    //Matching value not found
                    std::pair<int, int> valueIndex(nums[i], i);
                    hashMap.insert(valueIndex);
                } else {
                    //Matching value found
                    if (i > hashMap[matchingVal]) {
                        indices.push_back(hashMap[matchingVal]); //index of matching value
                        indices.push_back(i);
                    } else {
                        indices.push_back(i);
                        indices.push_back(hashMap[matchingVal]); //index of matching value
                    }
                    solutionFound = true;
                }
            }
        }
        //Note: complexity is O(n)
        if (solutionFound) {
            output(nums, target, indices);
        } else {
            std::cout << "No solution found.";
        }
        //Returning solution
        return indices;
    }

    std::vector<int> subOptimalTwoSum(std::vector<int>& nums, int target) {
        //Plan: check index 0 + all next indexes,
        //check index 1 + all next indexes, etc.
        //nums = [15, 7, 11, 2], target = 9
        //check 15+7 -> NO, check 15+11 -> NO, check 15+2 -> NO
        //check 7+11 -> NO, check 7+2 -> YES
        int total = 0;
        bool solutionFound = false;
        std::vector<int> indices;
        //Iterate through indices of vector except final index because there is no number to compare it to
        for(int i = 0; (i < (nums.size()-1)) && (solutionFound == false); i++) {
            //For each index, loop through the following indices and check if the sum == target
            for (int j = i+1; (j < nums.size()) && (solutionFound == false); j++) {
                total = nums[i]+nums[j];
                if (total == target) {
                    //If sum == target, store indices and set boolean to false to exit loops
                    indices.push_back(i);
                    indices.push_back(j);
                    solutionFound = true;
                }
            }
        }
        //Note: complexity is (n-1)(n-i-1) = O(n^2)
        if (solutionFound) {
            output(nums, target, indices);
        } else {
            std::cout << "No solution found.";
        }
        //Returning solution
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

    void output(std::vector<int>& nums, int& target, std::vector<int>& indices) {
        //Formatting output
        std::string vectorStr = vecToStr(nums);
        std::string targetStr = intToStr(target);
        std::string indicesStr = vecToStr(indices);
        std::string firstIndex = indicesStr.substr(1,1);
        std::string secondIndex = indicesStr.substr(3,1);
        std::cout << "Input: nums = " << vectorStr << ", target = " << targetStr << std::endl;
        std::cout << "Output: " << indicesStr << std::endl;
        std::cout << "Explanation: Because nums[" << firstIndex << "] + nums[" << secondIndex << "] == " <<
            targetStr << ", we return " << indicesStr << std::endl;
        return;
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
    std::vector<int> indices = solution.subOptimalTwoSum(nums, target);
    std::vector<int> indices2 = solution.twoSum(nums, target);
    return 0;
}