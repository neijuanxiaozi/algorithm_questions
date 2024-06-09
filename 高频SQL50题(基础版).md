#查询
1757. 可回收且低脂的产品 普通的select where 很简单不用看
584. 寻找用户推荐人 对于null值查不出来， 需要对null特殊处理 IS NULL 和 IS NOT NULL  https://leetcode.cn/problems/find-customer-referee/?envType=study-plan-v2&envId=sql-free-50
595. 大的国家 普通的select where 很简单不用看
1148. 文章浏览I 需要去重列关键字distinct 给列重命名as 对列排序order by 需要看 https://leetcode.cn/problems/article-views-i/description/?envType=study-plan-v2&envId=sql-free-50
1683.   无效的推文 需要判断某一列内容中的字符数 用CHAR_LENGTH()函数 需要再看 https://leetcode.cn/problems/invalid-tweets/description/?envType=study-plan-v2&envId=sql-free-50

1633. 各赛事的用户注册率 这题要求百分比 主要是找分子和分母  分母可以直接写select语句放在分母上 这样就好写了 https://leetcode.cn/problems/percentage-of-users-attended-a-contest/description/?envType=study-plan-v2&envId=sql-free-50
1211. 查询结果的质量和占比  如果想计算满足某个条件的列的数量   因为要用条件所以用sum 但是指向计算数量 就把满足条件的列用1替换 不满足用0  sum(if(rating < 3, 1, 0))  count也可以用if 替换时不满足的用null替换  https://leetcode.cn/problems/queries-quality-and-percentage/?envType=study-plan-v2&envId=sql-free-50

#连接

笛卡尔积查询:
    笛卡尔积查询是连接查询中的一种特殊情况，它是指在没有指定任何连接条件的情况下，将两个或多个表中的每一行都进行组合，得到的结果称为笛卡尔积。
    笛卡尔积查询问题:
    1. 据量膨胀：当表A和表B中的记录数较大时，笛卡尔积查询会导致结果集中的记录数量急剧增加，从而增加了查询的时间和资源消耗。
    2. 结果不准确：由于没有指定连接条件，笛卡尔积查询会将所有记录进行组合，可能会得到一些无意义或重复的结果。
```
SELECT * FROM A, B;
```

内连接:
    内连接是连接查询中最常用的一种方式，它只返回满足连接条件的记录。使用内连接可以避免笛卡尔积查询的问题。
```
SELECT * FROM A
INNER JOIN B ON A.id = B.id;
```

外连接:
    外连接查询是连接查询中的一种常见类型，它可以返回左表和右表中的所有记录，以及满足连接条件的记录。外连接查询可以进一步分为左外连接和右外连接。
    左连接和右连接：
    左连接和右连接是连接查询中的两种常见类型，它们分别返回左表和右表中的所有记录，以及满足连接条件的记录。
```
-- 左连接 左外连接是指将左表中的所有记录和右表中满足连接条件的记录进行关联查询。如果右表中没有满足连接条件的记--录，则会返回NULL值。
SELECT * FROM A
LEFT JOIN B ON A.id = B.id;

-- 右连接 右外连接是指将右表中的所有记录和左表中满足连接条件的记录进行关联查询。如果左表中没有满足连接条件的记录，则会返回NULL值。
SELECT * FROM A
RIGHT JOIN B ON A.id = B.id;
```

1378. 使用唯一标识码替换员工ID  需要连接 然后还需要包含第一个表的所有行 使用左连接left join 因为要包含第一个表的所有行 就from第一个表 然后left join第二个表 然后条件用on https://leetcode.cn/problems/replace-employee-id-with-the-unique-identifier/description/?envType=study-plan-v2&envId=sql-free-50

1581. 进店却为进行过交易的顾客 需要先将两个表左连接 然后查第一个表里的悬浮元组 最后在根据id分组 用count计算数量 https://leetcode.cn/problems/customer-who-visited-but-did-not-make-any-transactions/?envType=study-plan-v2&envId=sql-free-50

197. 上升的温度 需要用到datediff函数算两天日期差  返回值是第一个参数减去第二个参数的值  https://leetcode.cn/problems/rising-temperature/description/?envType=study-plan-v2&envId=sql-free-50

1661. 每台机器的进程平均运行时间 主要还是连接问题 很多问题单表操作不了 时刻记得自连接 然后住处符合标准的 之后进行计算插值 计算avg round(avg, 3) 保留三位  然后按id分组  https://leetcode.cn/problems/average-time-of-process-per-machine/description/?envType=study-plan-v2&envId=sql-free-50

57. 员工奖金 左外连接 没难度 不用看 https://leetcode.cn/problems/employee-bonus/description/?envType=study-plan-v2&envId=sql-free-50

1280. 学生们参加各科测试的次数 用了子查询和两次连接 一个是cross join交叉联接相当于笛卡尔积 然后左连接子查询 然后用了函数 ifnull(attended_exams, 0) as attended_exams 用0替换空值 需要重新看 https://leetcode.cn/problems/students-and-examinations/description/?envType=study-plan-v2&envId=sql-free-50

570. 至少有5名直接下属的经理  大致思路想对了 但是语法有错误 在group by之后 想对group by的结果做count再做大小比较 需要用having count(managerID) >= 5  而且这句having 要写在group by语句之后 https://leetcode.cn/problems/managers-with-at-least-5-direct-reports/?envType=study-plan-v2&envId=sql-free-50

1934. 确认率 需要看  主要是用到了avg(c.action='confirmed') 可以很方便计算  https://leetcode.cn/problems/confirmation-rate/description/?envType=study-plan-v2&envId=sql-free-50




#聚合函数
620. 有趣的电影 在where条件中 对id使用聚合函数mod(id, 2) = 1   https://leetcode.cn/problems/not-boring-movies/?envType=study-plan-v2&envId=sql-free-50
1251. 平均售价 用到sum函数 https://leetcode.cn/problems/average-selling-price/description/?envType=study-plan-v2&envId=sql-free-509
1174. 即时食物配送II 主要是可以在where中使用in一个子查询 
where
    (customer_id, order_date) 
    in (...)
https://leetcode.cn/problems/immediate-food-delivery-ii/?envType=study-plan-v2&envId=sql-free-50
550. 游戏玩法分析IV  先用子查询将player_id和最小event_date查出来  然后再基于这个查询去查。 https://leetcode.cn/problems/game-play-analysis-iv/description/?envType=study-plan-v2&envId=sql-free-50


#排序和分组
2356. 每位教师所教授的科目种类的数量 在count(distinct subject_id)函数中可以用distinct https://leetcode.cn/problems/number-of-unique-subjects-taught-by-each-teacher/description/?envType=study-plan-v2&envId=sql-free-50
1141. 查询近30天活跃用户数 做对了 使用了 datediff  
1084. 销售分析III 使用group by后 用having做条件 having count(sale_date between '2019-01-01' and '2019-03-31' or null) = count(*) https://leetcode.cn/problems/sales-analysis-iii/?envType=study-plan-v2&envId=sql-free-50
596. 超过5名学生的课 很简单group by加having 直接秒了
1729. 求关注着的数量 和上题一样 加个order by就行了 直接秒了
619. 只出现一次的最大数字  如果是空表什么都不会输出 但是加个max avg等聚合函数空表时会输出一个null https://leetcode.cn/problems/biggest-single-number/solutions/683252/dang-biao-ge-wei-kong-shi-ru-he-fan-hui-6qpzg/?envType=study-plan-v2&envId=sql-free-50
1045. 买下所有产品的用户 直接用count本表的字段 和另外一个表count的数量相比     count(distinct product_key) = (select count(*) from Product) https://leetcode.cn/problems/customers-who-bought-all-products/description/?envType=study-plan-v2&envId=sql-free-50


#高级查询和连接
UNION和UNIONALL关键字将两个结果集合并为一个，但是有区别 UNION回去除重复的记录 UNIONALL合并之后直接返回


1731. 每位经理的下属员工数量 自己做出来了 但是我多写了非空条件 其实在表连接后就不会出现非空字段了 不用判断空 
1789. 员工的直属部门 使用UNION联合查询 从一张表中查询两种不同条件的结果  https://leetcode.cn/problems/primary-department-for-each-employee/description/?envType=study-plan-v2&envId=sql-free-50
610. 判断三角形 最终的查询字段中可以用多条件case when 
    select 
    x, 
    y, 
    z, 
    case 
        when x + y > z and x + z > y and y + z > x then "Yes"
        else "No"
    end as "triangle"
from 
    Triangle 
https://leetcode.cn/problems/triangle-judgement/?envType=study-plan-v2&envId=sql-free-50  
180. 连续出现的数字  不会也没做  跳过去了
1164. 指定日期的产品价格 