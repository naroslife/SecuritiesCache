#include "gtest/gtest.h"
#include "Cache.h"

TEST(SecuritiesCacheTest, add) {
    Cache myCache;
    Order myOrder{"id1", "sec1", "user1", "company1", "sell", 100};
    Order myOrder2{"id1", "sec2", "user2", "company2", "sell", 100};
    try {
        myCache.addOrder(myOrder);
    } catch (const std::logic_error& ex) {
        FAIL() << "Unexpectedly thrown";
    }
    try {
        myCache.addOrder(myOrder2);
        FAIL() << "Should have thrown";
    } catch (const std::logic_error& ex) {
        std::cout << "Thrown as expected";
    }


}

TEST(SecuritiesCacheTest, cancelByOrderId) {
    Cache myCache;
    Order myOrder{"id1", "sec1", "user1", "company1", "sell", 100};
    Order myOrder2{"id2", "sec2", "user2", "company2", "sell", 100};
    try {
        myCache.addOrder(myOrder);
        myCache.addOrder(myOrder2);
        EXPECT_NE(myCache.getOrders()->find(Order("id1")), myCache.getOrders()->end());
        EXPECT_NE(myCache.getOrders()->find(Order("id2")), myCache.getOrders()->end());
        myCache.cancelByOrderId("id2");
        EXPECT_EQ(myCache.getOrders()->find(Order("id2")), myCache.getOrders()->end());
    } catch (const std::logic_error& ex) {
        FAIL() << "Unexpectedly thrown";
    }
}

TEST(SecuritiesCacheTest, cancelByUserId) {
    Cache myCache;
    Order myOrder{"id1", "sec1", "user1", "company1", "sell", 100};
    Order myOrder2{"id2", "sec2", "user1", "company2", "sell", 100};
    Order myOrder3{"id3", "sec3", "user2", "company2", "sell", 100};
    try {
        myCache.addOrder(myOrder);
        myCache.addOrder(myOrder2);
        myCache.addOrder(myOrder3);
        EXPECT_NE(myCache.getOrders()->find(Order("id1")), myCache.getOrders()->end());
        EXPECT_NE(myCache.getOrders()->find(Order("id2")), myCache.getOrders()->end());
        EXPECT_NE(myCache.getOrders()->find(Order("id3")), myCache.getOrders()->end());
        myCache.cancelByUserId("user1");
        EXPECT_TRUE(myCache.getOrders()->size() == 1);
    } catch (const std::logic_error& ex) {
        FAIL() << "Unexpectedly thrown";
    }
}

TEST(SecuritiesCacheTest, cancelBySecuritiesId) {
    Cache myCache;
    Order myOrder{"id1", "sec1", "user1", "company1", "sell", 100};
    Order myOrder2{"id2", "sec2", "user1", "company2", "sell", 100};
    Order myOrder3{"id3", "sec2", "user2", "company2", "sell", 1000};
    try {
        myCache.addOrder(myOrder);
        myCache.addOrder(myOrder2);
        myCache.addOrder(myOrder3);
        EXPECT_NE(myCache.getOrders()->find(Order("id1")), myCache.getOrders()->end());
        EXPECT_NE(myCache.getOrders()->find(Order("id2")), myCache.getOrders()->end());
        EXPECT_NE(myCache.getOrders()->find(Order("id3")), myCache.getOrders()->end());
        myCache.cancelBySecurityId("sec2", 500);
        EXPECT_TRUE(myCache.getOrders()->size() == 2);
        EXPECT_NE(myCache.getOrders()->find(Order("id2")), myCache.getOrders()->end());
        EXPECT_EQ(myCache.getOrders()->find(Order("id3")), myCache.getOrders()->end());
    } catch (const std::logic_error& ex) {
        FAIL() << "Unexpectedly thrown";
    }
}

TEST(SecuritiesCacheTest, match) {
    Cache myCache;
    Order myOrder{"id1", "US5422358DA3", "user2", "companyB", "sell", 3000};
    Order myOrder2{"id2", "US5422358DA3", "user4", "companyC", "buy", 600};
    Order myOrder3{"id3", "US5422358DA3", "user5", "companyB", "buy", 100};
    Order myOrder4{"id4", "US5422358DA3", "user7", "companyE", "buy", 2000};
    Order myOrder5{"id5", "US5422358DA3", "user8", "companyE", "sell", 5000};
    try {
        myCache.addOrder(myOrder);
        myCache.addOrder(myOrder2);
        myCache.addOrder(myOrder3);
        myCache.addOrder(myOrder4);
        myCache.addOrder(myOrder5);

        double matched = myCache.match("US5422358DA3");
        ASSERT_EQ(matched, 2700.0);
    } catch (const std::logic_error& ex) {
        FAIL() << "Unexpectedly thrown";
    }

}