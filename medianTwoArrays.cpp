/*
Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.
The overall run time complexity should be O(log (m+n)).

Example 1:

Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.

Example 2:

Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.

Constraints:

nums1.length == m
nums2.length == n
0 <= m <= 1000
0 <= n <= 1000
1 <= m + n <= 2000
-106 <= nums1[i], nums2[i] <= 106
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <iomanip>

class Solution {
    const static int CUTOFF = 10;
public:
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
        double median = 0.00000;
        std::cout << "nums1.size() == " << nums1.size() << std::endl;
        std::cout << "nums2.size() == " << nums2.size() << std::endl;
        //std::cout << "nums2 == " << vecToStr(nums2) << std::endl;

        //Plan: mergesort algorithm maybe?

        std::vector<int> combinedVectors (nums1.size()+nums2.size());
        int j = 0;
        for (int i = 0; i < combinedVectors.size(); i++) {
            if (i < nums1.size()) {
                combinedVectors[i] = nums1[i];
            } else {
                combinedVectors[i] = nums2[j];
                j++;
            }
        }
        combinedVectors = mergeSort(combinedVectors);
        std::cout << "combinedVectors.size() == " << combinedVectors.size() << std::endl;
        std::cout << "combinedVectors after mergeSort == " << vecToStr(combinedVectors) << std::endl;
        if (combinedVectors.size()%2 != 0) {
            //odd number -> median is one number
            std::cout << "Odd number of values in vector." << std::endl;
            median = double(combinedVectors[(combinedVectors.size() - 1) / 2]);
        } else {
            //even number -> median is average of two numbers
            std::cout << "Even number of values in vector." << std::endl;
            int mid1 = (combinedVectors.size() - 2) / 2;
            int mid2 = combinedVectors.size() / 2;
            median = (double(combinedVectors[mid1]) + double(combinedVectors[mid2])) / 2;
            std::cout << "combinedVectors[mid1] == " << combinedVectors[mid1] << std::endl;
            std::cout << "combinedVectors[mid2] == " << combinedVectors[mid2] << std::endl;
        }
        std::cout << std::setfill('0') << std::setw(10) 
          << std::fixed << std::setprecision(5) << "median == "<< median << std::endl;

        return median;
    }

    std::vector<int> insertionSort (std::vector<int>& nums){
        for (int i = 1; i < nums.size(); i++) {
        	for (int j = i; ((j > 0) && (nums[j - 1] > nums[j])); j--) {
        		int tmp = nums[j];
        		nums[j] = nums[j - 1];
        		nums[j - 1] = tmp;
        	}
        }
    	return nums;
    }
    
    std::vector<int> mergeSort (std::vector<int>& nums) {
		 nums = sort(nums, 0, (nums.size() - 1) / 2, nums.size() - 1);
		 return nums;
    }
    
    //[13,12,11,10,9,8,7,6,5,4,3,2,1]
    //[lo,x,x,x,x,x,mid,x,x,x,x,x,hi]
    //[0,1,2,3,4,5,6,7,8,9,10,11,12]
    //[lo,x,x,mid,x,x,hi]|[lo,x,x,mid,x,x,hi]
    //[7,8,9,10,11,12,13,6,5,4,3,2,1]|[7,8,9,10,11,12,13,1,2,3,4,5,6]
    //100,000 -> 10+10+10... 100,000/10 = 10,000 n/10 insertion sorts
    //100,000,000 -> 10+10+10... 100,000,000/10 = 10,000,000 = n/10 insertion sorts
    //n/10 insertion sorts = n/10*n^2 -> O(n^3)????

    std::vector<int> sort (std::vector<int>& nums, int lo, int mid, int hi) {
    	if ((hi - lo) <= CUTOFF) {
    		std::vector<int> newVector ((hi - lo) + 1);
    		for (int i = 0, j = lo; i < newVector.size(); i++, j++) {
    			newVector[i] = nums[j];
    		}
    		newVector = insertionSort(newVector);
    		for (int i = 0, j = lo; i < newVector.size(); i++, j++) {
    			nums[j] = newVector[i];
    		}
    		return nums;
    	}
    	nums = sort(nums, lo, (lo + ((mid - lo) / 2)), mid);
    	nums = sort(nums, (mid + 1), ((mid + 1) + ((hi - mid) / 2)), hi);
    	return merge(nums, lo, mid, hi);
    }
    
    std::vector<int> merge (std::vector<int>& nums, int lo, int mid, int hi) {
    	std::vector<int> newVector ((hi - lo) + 1);
		for (int i = 0, j = lo; i < newVector.size(); i++, j++) {
			newVector[i] = nums[j];
		}
		int x = 0;
		int y = (mid - lo) + 1;
		int xLimit = y - 1;
		int yLimit = newVector.size() - 1;
        int i = 0;
    	for (i = lo; ((i <= hi) && (x <= xLimit) && (y <= yLimit)); i++) {
    		if (newVector[x] <= newVector[y]) {
    			nums[i] = newVector[x];
    			x++;
    		}
    		else {
    			nums[i] = newVector[y];
    			y++;
    		}
    	}
    	while (x <= xLimit) {
    		nums[i] = newVector[x];
    		i++;
    		x++;
    	}
    	while (y <= yLimit) {
    		nums[i] = newVector[y];
    		i++;
    		y++;
    	}
    	return nums;
    }

    std::string vecToStr(std::vector<int>& nums) {
        std::stringstream ss;
        copy(nums.begin(), nums.end(), std::ostream_iterator<int>(ss,","));
        std::string str = ss.str();
        str = str.substr(0, str.length()-1); //Trimming trailing comma
        std::string finalStr = "[" + str + "]";
        return finalStr;
    }
};

int main() {
    //1 <= m + n <= 2000
    Solution solution;
    std::srand(std::time(nullptr));
    std::vector<int> nums1;
    std::vector<int> nums2;
    const int vectorSizeM = std::rand()%1001; //0 <= m <= 1000
    //std::cout << "vectorSizeM == " << vectorSizeM << std::endl;
    const int vectorSizeN = std::rand()%1001; //0 <= n <= 1000
    //std::cout << "vectorSizeN == " << vectorSizeN << std::endl;
    const int maxNumber = 10000000; //-10^6 <= nums1[i], nums2[i] <= 10^6
    //nums1.length == m
    for (int i = 0; i < vectorSizeM; i++) {
        nums1.push_back(std::rand()%maxNumber); //only positive ints atm
    }
    //nums1.length == n
    for (int i = 0; i < vectorSizeN; i++) {
        nums2.push_back(std::rand()%maxNumber); //only positive ints atm
    }
    //double median = solution.findMedianSortedArrays(nums1, nums2);
    std::vector<int> testNums1;
    testNums1.push_back(1);
    testNums1.push_back(2);
    std::vector<int> testNums2;
    testNums2.push_back(3);
    testNums2.push_back(4);
    double median = solution.findMedianSortedArrays(testNums1, testNums2);
    return 0;
}