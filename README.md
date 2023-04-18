### gin_mall_qt

gin_mall_qt是一款基于qt框架的电子商城前端，电子商城后端使用go语言基于gin框架实现。

目前实现了仅登陆注册及界面之间的跳转。

To do list:

1. 界面全球化。---done

2. CMake工程改造。

3. Debian打包配置。---done

4. 购物车\主页面\个人中心．．．


全球化

1. 使用lupdate生成ts文件

```bash
lupdate gin_mall_qt.pro -ts translations/i18n_zh_cn.ts
```

2. 使用Qt Linguists打开并编辑生成的ts文件
3. 使用lrelease生成qm文件

```bash
lrelease translations/i18n_zh_cn.ts -qm translations/i18n_zh_cn.qm　
```

​    4.使用Qt Creator添加一个qrc文件，包含要使用的语言资源文件

# 参考

https://www.jianshu.com/p/71f738364410

https://www.cnblogs.com/oloroso/p/4596740.html

https://blog.csdn.net/maizousidemao/article/details/127033800?ydreferer=aHR0cHM6Ly93d3cuZ29vZ2xlLmNvbS5oay8%3D

https://zhuanlan.zhihu.com/p/603853479

## License

This project is licensed under [GPLv3](LICENSE) or any later version.
