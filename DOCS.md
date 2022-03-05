# INFO ABOUT REDIS AND FUNCTIONS PROVIDED BY US.

Redis supports different kinds of abstract data structures, such as strings, lists, maps, sets, sorted sets, etc.

** Redis is a key-value in memory database (meaning, data will be kept in main memory, which is non-volatile storage)* *
Redis supports PUBLISH/SUBSCRIBE messaging paradig where senders are not programmed to send their messages to specific recivers.
See more in official website https://redis.io/documentation.

## Redis main privileges:: it's simple to use; scalable; and fast; 

 
# MAIN IDEA
As you can see here: https://redis.io/community Redis appreciates improvements, bug fixes even features related we decided to implement
basic functionality with stream sockets/ up to 5 users via network. You can change ip_address in src/client_server/client.cpp
&& src/client_server/server.cpp before building.

# HOW TO USE (DATA TYPES)

LIST supportes 4 functions LPUSH, RPUSH, LRANGE, LTRIM. 

SET supportes SADD, SMEMBERS, RSMEMBERS, and SPOP.

STRING supportes APPEND, SET and GET. 

And finally PRIORITY_QUEUE supports ZREVRENGE, ZREM, ZADD, ZRENGE.

** Info about data types in details you can see in README.md **
