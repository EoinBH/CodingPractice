



class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        double mean = 0.00000;

        return mean;
    }
};

int main() {
    //1 <= m + n <= 2000
    Soltution solution;
    std::srand(std::time(nullptr));
    std::vector<int> nums1;
    std::vector<int> nums2;
    const int vectorSizeM = 1000; //0 <= m <= 1000
    const int vectorSizeN = 1000; //0 <= n <= 1000
    const int maxNumber = 10000000; //-10^6 <= nums1[i], nums2[i] <= 10^6
    //nums1.length == m
    for (int i = 0; i < vectorSizeM; i++) {
        nums1.push_back(std::rand()%maxNumber);
    }
    //nums1.length == n
    for (int i = 0; i < vectorSizeN; i++) {
        nums2.push_back(std::rand()%maxNumber);
    }
    double mean = findMedianSortedArrays(nums1, nums2);
    return 0;
}