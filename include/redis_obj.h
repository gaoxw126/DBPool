#ifndef _REDIS_OBJ_H
#define _REDIS_OBJ_H

#include <hiredis/hiredis.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "debug.h"

using std::string;
using std::vector;

// 设置一个标志,函数参数列表当中带有OUT的就是输出引用,带有IN的就是输入参数
#define OUT
#define IN

class RedisObj
{
 public:
	RedisObj(string HostIP, string pPassword, unsigned iPort);
	virtual ~RedisObj();
	// Dump指的是把m_pRedis的指针指向的值打印出来
	void Dump() const;

	string ErrorMessage();

	// 根据成员变量来建立Redis连接
	bool Connect();
	void Close();
	
	int ExecuteCmd(const char* pCmd);

	//返回Redis的指针
	redisContext* get() const;

 public: 
	// 从redis当中获取返回值
	int IntegerResult(OUT long long &result);
	int StringResult(OUT string &result);
	int StatusResult(OUT string &result);
	int StringArrayResult(OUT vector<string> &result);
	int ArrayResult(OUT vector<redisReply*> &result);
	
 private:
	// 从redis当中获取返回值
	int IntegerResult(OUT long long &result, IN redisReply* reply);
	int StringResult(OUT string &result, IN redisReply* reply);
	int StatusResult(OUT string &result, IN redisReply* reply);
	int StringArrayResult(OUT vector<std::string> &result, IN redisReply* reply);
	int ArrayResult(OUT vector<redisReply*> &result, IN redisReply* reply);

 private:
	// 代表了一条数据库连接
	redisContext* r_pRedis;
	redisReply* r_pResult;
 private:
	// 连接必备的参数:IP地址,用户,密码,数据库名称,端口号
	string r_strHost;
	string r_strPassword;
	unsigned r_iPort;

	//错误信息
	string r_strErrorMessage;
};

// 尝试使用shared_ptr来代替RedisObj*
typedef boost::shared_ptr<RedisObj>RedisObjPtr;

#endif /* REDIS_OBJ_H */
