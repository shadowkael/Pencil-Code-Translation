#第十二章 使用 JQuery遍历数据
##12.0.1 学习目标
本章节介绍了jquery的基础知识。当今许多开发者使用jquery来创建具有交互式功能的网页，让学生熟悉、了解互联网上大量的jquery编程资源。学生将学习jquery的”选择”概念，并使用jquery的方法和事件来创建一个简单的交互程序。
##12.0.2 主题大纲
###12.0 章节介绍
* 12.0.1 目标
* 12.0.2 主题大纲
* 12.0.3 关键术语
* 12.0.4 关键概念
###12.1 课程计划
* 12.1.1 建议的时间表
* 12.1.2 CSTA标准
* 12.1.3 课程计划I——使用定时器Timer()程序
* 12.1.4 课程计划II——遍历数组
##12.0.3 关键术语
<img src="images/12/1.png">
##12.0.4 关键概念
* 介绍jQuery

因为JQuery以一种方便简单的方法来检查和改变视觉元素，所以JQuery在网页的创建中最受欢迎的库。下面是一个使用jquery的例子。

						‘$(‘div’).hide();’

在使用jquery时需要以下三个步骤：

1.CSS选择器是用来查找页面上的一组元素。

2.创建一个jquery对象用来表示集合元素。

3.调用jquery方法来对集合元素做一些相应的操作。

在这个例子中，’div’是CSS选择器，$(‘div’)是jquery对象，.hide()是jquery方法。

这行jquery代码的意思是：“查找页面上所有的<div>元素并将其隐藏”。
查询数据库包括查找、收集和操作三个步骤。Jquery将这个数据库技术应用于一个HTML页面的界面元素，将单个页面作为数据库。

使用$创建jquery对象

在jquery库中最重要的函数是创建jquery的对象函数。因为它使用频繁，Jquery库为这个函数提供了一个简短而不寻常的名字：$。尽管它可能看起来很奇怪，$恰好可以使用一个符号作为一个普通的函数名。
一个jquery对象拥有一组元素：在网页上可能包含零个，一个或者多个元素。
下面是一些使用$的例子：

<table>
<tr>
  <td>jquery构造器</td>
  <td>创建一个包含这个集合的jquery对象</td>
</tr>
<tr>
 <td>$('P')</td>
 <td>文档中所有的`<p>`元素</td>
</tr>
<tr>
 <td>$('.special')</td>
 <td>文档中所有class='special'的元素</td>
</tr>
<tr>
 <td>$('#buy')</td>
 <td>文档中id='buy'的元素</td>
</tr>
<tr>
 <td>$(`<img src="/img/cat">`)</td>
 <td>没有插入文档中的一个新的`<img>`元素的src</td>
</tr>
<tr>
 <td>$(`<p>Hello</p>`)</td>
 <td>还未插入文档中的一种给定文本内容的新`<p>`元素</td>
</tr>
</table>

用于查找元素的$ CSS选择器语言和CSS语言相同，因此你了解的CSS选择器也同样可以应用到jquery中。如果没有元素匹配选择器，函数将返回为空集。
$函数也可以使用HTML语法创建元素（如上面的最后两个例子）。在这种情况下，它返回一组尚未放置在可视文档中新创建的元素。jquery对象有一个设置其大小的.length的长度属性。例如，可以使用表达式$(‘P’).length来计算文档中的p元素的数量。

使用jquery对象

有若干可用于任何jquery对象的操作方法。例子如下：
<table>
<tr>
  <td>$('p').fadeOut();</td>
  <td>平滑的淡出元素，然后隐藏它们。</td>
</tr>
<tr>
 <td>  $('p').css({ background: red });</td>
 <td>改变所有选定元素的CSS样式</td>
</tr>
<tr>
 <td>  $('p').html('Read <b>this</b>');</td>
 <td>替换所有选定元素的HTML内容</td>
</tr>
<tr>
 <td> var t = $('p').text();   </td>
 <td>读取第一个选定的`<p>`元素的文本内容</td>
</tr>
<tr>
 <td> $('input').val(10); </td>
 <td>设置所有选定的`<input>`框内的值</td>
</tr>
<tr>
 <td>$('img).attr({src: '/img/cat'});</td>
 <td>改变每个`<img>`元素的src属性为"/img/cat"</td>
</tr>
<tr>
 <td>$(`'<img src="/img/dog">'`).appendTo('body');</td>
 <td>创建一个dog图像并将它添加到`<body>`中</td>
</tr>
<tr>
 <td>$('#warn').remove();</td>
 <td>删除id="warn"的元素</td>
</tr>
<tr>
 <td>$('img').bk(100);</td>
 <td>使用"bk"函数移除`<img>`元素</td>
</tr>
</table>

使用过Pencil Code的每个学生都会对Jquery有所熟悉，因为每个Pencil Code语言都是一个jquery对象。这个Pencil Code语言库为jquery方法增加了像”pen”，”fd”，”rt”，和”moveto”等语言方法，是jquery的一个延伸语言。程序员可以使用这些方法在屏幕上移动任何视觉元素。

主要的语言可以使用jquery方法$(‘#turtle’)调用，所以他们的CoffeeScript程序”fd 100”与本书第一部分的JavaScript和jQuery程序$(‘#turtle’).fd(100)是一样的。

尝试使用jQuery

这样有利于学生对个别jQuery方法进行测试。下面的HTML就是应用”gear”菜单来创建的Pencil Code项目。

`<html>` 

`<body> `
   
`<h1>My favorite things</h1>` 
  
 `<p>Pizza: <img src="/img/pizza"></p>`      
   
`<p>Watermelon: <img src="/img/t-watermelon"></p>`

`</body>` 

`</html> `

该文档中有足够的元素可以用上面所介绍的jQuery实例进行测试。学生可以进入Pencil Code右窗格“测试面板”中的jQuery代码，或者也进入运行在左边的JavaScript和CoffeeScript代码中。

这里的jQuery有两点需要注意：

1.当您运行该代码时，通常都会更改，虽然有些更改可以随着时间的推移而改变。

2.尽管你所做的更改会影响可视文档，但是它们不改变程序本身的HTML。
程序中的HTML是“初始状态”的HTML页面。一旦一个程序添加、删除或者改变元素，它可以结束寻找程序员最初写的HTML页面，但是如果程序运行时，它将从最初的HTML开始。

使用jQuery提供动态输出

jQuery是用于创建随时间而改变的动态输出屏幕的用户界面。例如，你可以利用jQuery控制一个定时器每一秒更新多次。下面这个JavaScript程序可以做到这一点。

`$('<h1>Countdown</h1>').appendTo('body'); `

`$('h1').css({textAlign: 'center'});` 

`var count = 10; `

`forever(1, function() { `
    
     `$('h1').html(count); `
   
     `count -=1; `
   
   ` if (count < 0) {`
     
     `$('h1').html('blast off!'); `
      
      stop(); 
`}` 

`}); `

本程序使用“forever”来设置一个每秒被调用一次直到stop()方法被调用的函数。以下是程序中每一个jQuery调用的解释：

<table>
<tr>
  <td>$(`'<h1>Countdown</h1>'`).appendTo('body');</td>
  <td>创建一个`<h1>`元素，并将其添加到<body>中</td>
</tr>
<tr>
 <td>  $('h1').css({textAlign: 'center'});</td>
 <td>设置元素`<h1>`中的“text-align”属性为中心样式</td>
</tr>
<tr>
 <td>   $('h1').html(count);</td>
 <td>将元素<h1>中的HTML内容更改为可变的</td>
</tr>
<tr>
 <td>$('h1').html('blast off!');</td>
 <td>将元素<h1>中的HTML的内容变为“blast off！”</td>
</tr>
<tr>
</table>



