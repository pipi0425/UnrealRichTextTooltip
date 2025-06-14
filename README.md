# UnrealRichTextTooltip （中文在后面）

## Other people's work and discussion for reference:
- discussion about tooltip: https://forums.unrealengine.com/t/tooltip-rich-text-decorator/128714
- basic rich text style and rich text image usage tutorial: https://www.unrealengine.com/en-US/tech-blog/advanced-text-styling-with-rich-text-block
- rich-text tooltip using built-in tooltip widget: https://github.com/Nauja/ue4-richtextblocktooltip-sample
- another guy's fork of the previous repo to create a button in rich text: https://github.com/OsirisDeveloper/ue4-richtextblocktooltip-sample

## What is different in this repo
the 3rd link above does have a working tooltip for rich text, but the tooltip only contains text.  
e.g. an in-game term that players can hover to show details as text, then tooltip text is fine, but if an in-game skill, when hovered, the player may want to see more details formatted in a widget.

## How this repo works
In `FRichInlineTooltip::CreateDecoratorWidget` check if valid then put a UUserWidget created in `URichTextBlockTooltipDecorator::CreateTooltipWidget` into the tooltip.

## How to use
- Place the two files into your source and compile. You may need to add `"Slate"` and `"SlateCore"` to your build.cs's `PublicDependencyModuleNames` (maybe also UMG? I added UMG for another functionality in my project so I don't know if it is needed.)
- In UE, create BP with parent `URichTextBlockTooltipDecorator`.
- Set the text style variable of BP_RichTextBlockTooltipDecorator (otherwise you may see purple blocks)
- Override `CreateTooltipWidget`. Notice that directly creating widgets here may cause errors (world context issue). My solution is: cast the player controller to my player controller, then, in my player controller create a function that inputs the id string and outputs a UUserWidget. Alternatively, you can also create blueprint interface and implement that interface in your player controller to avoid casting.
- Add your BP_RichTextBlockTooltipDecorator to your richtextblocks' decorator classes.
- In richtextblocks, write `<tooltip id="xxx">yyy</>` to use.

## Other info
- tested in UE 5.4.4-35576357, works both in editor and shipping build.
- known issue: the tooltip has a background, either remove your background in your widget blueprint, or edit the CreateDecoratorWidget function to remove the tooltip's background (have not tested yet)
- if anyone wants to use this repo as a starting point to create more decorators, you may also want to take a look at UE's built-in image decorator's implementation:
  - Engine/Source/Runtime/UMG/Public/Components/RichTextBlockImageDecorator.h
  - Engine/Source/Runtime/UMG/Private/Components/RichTextBlockDecorator.cpp

---
## 之前一些其他人的讨论和repo
- UE forum的讨论: https://forums.unrealengine.com/t/tooltip-rich-text-decorator/128714
- UE内置的style和image decorator的使用教程: https://www.unrealengine.com/en-US/tech-blog/advanced-text-styling-with-rich-text-block
- 这位实现了tooltiptext: https://github.com/Nauja/ue4-richtextblocktooltip-sample
- 这位基于上面那个写的button: https://github.com/OsirisDeveloper/ue4-richtextblocktooltip-sample

## 本repo的区别
上面第三个链接（Nauja）的repo是实现了tooltiptext，但是有的使用情景只是text不够，想显示更多内容，或者不喜欢默认tooltip的风格，又不想在C++里写slate，本repo实现了把蓝图里的createwidget出来的UUserWidget做成richtext tooltip的功能。

## 原理
`FRichInlineTooltip::CreateDecoratorWidget`里调用`URichTextBlockTooltipDecorator::CreateTooltipWidget`，而后者是BlueprintImplementableEvent，可在蓝图里override。

## 使用方法
- .h和.cpp文件放入源码，编译。需要在build.cs里的依赖模块里添加Slate和SlateCore（我自己的项目之前就添加了UMG因此不知道需不需要，如果没加UMG编译不出来就加上咯）
- 回到UE Editor里以`URichTextBlockTooltipDecorator`为父类创建蓝图。
- 蓝图中设置textstyle，不改的话默认font好像没字体，会出现紫块。
- 蓝图中override `CreateTooltipWidget`。注意直接在此`CreateWidget`以及执行其他的一些需要world context的东西会出错（这也就是为什么我在此放了一个playercontroller）。我的解决方案是把playercontroller转成自己的playercontroller然后去那边写CreateWidget和其他逻辑。（你也可以做Blueprint Interface蓝图接口然后你的playercontroller去实现接口）
- 把这个tooltip decorator的蓝图加到你richtextblock的decorator classes里去。
- 在richtextblock里写`<tooltip id="阿巴阿巴">阿巴阿巴阿巴</>`来使用。

## 补充信息
- 我在UE 5.4.4-35576357里测的，editor和打包出来都可用。
- 已知问题：这个tooltip会自带一个背景，要么把你蓝图里的widget背景删掉，要么去改CreateDecoratorWidget函数，我懒得改了。
- 如果你要以此为基础写其他的decorator，可以看看UE内置的image decorator的实现，位置在：
  - Engine/Source/Runtime/UMG/Public/Components/RichTextBlockImageDecorator.h
  - Engine/Source/Runtime/UMG/Private/Components/RichTextBlockDecorator.cpp
