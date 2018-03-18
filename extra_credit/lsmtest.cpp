#include "lsm.h"
#include "gtest/gtest.h"
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <vector>
#include <cmath>
#include <string>

TEST(TEST, Insert10000) {
    LSM<int, int> tree;
    std::map<int, int> mymap;
    for(int i = 0; i < 10000; i++){
        tree.insert(std::make_pair(i, i));

        mymap[i] = i;
    }

    for(int j=0; j<10000; j++)
    {
        EXPECT_EQ(mymap[j], tree.find(j)->second);
    }
}

TEST(TEST, DuplicateInsert100) {
    LSM<int, int> tree;

    for(int i =0; i<10000; i++) {
        tree.insert(std::make_pair(i, i));
        tree.insert(std::make_pair(i, 0));  
    }

    for(int i =0; i<10000; i++) EXPECT_EQ(0, tree.find(i)->second);
}

TEST(TEST, BranchCheck)
{
    for(int count = 0; count<5; count++)
    {
        LSM<int, std::string> tree;
        int length = pow(count,5);
        for(int i = 0; i < length; i++){
            tree.insert(std::make_pair(i, "hi"));
        }

        std::vector<std::vector<std::pair<const int, std::string> > > thetree = tree.getmTree();

        for(unsigned int i = 0; i<thetree.size(); i++)
        {
            if(thetree[i].size() != 0)
            {
                EXPECT_EQ((int)pow(2,i), thetree[i].size());
            }
        }
    }
}