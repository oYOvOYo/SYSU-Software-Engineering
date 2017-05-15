# 现代操作系统应用开发实验报告

最开始试图使用mediaplayer，然后进度条部分就很难写，异步线程就会出各种各样的问题。求正确打开姿势

## 实现说明

> 本项目实现了较为基本的播放视频/音频功能。

以下要求已经全部实现。

```
具体要求：
1.可暂停，播放，停止等操作。
2.要有进度条，实时显示媒体的播放进度；同时，通过拖动进度条，也可以使媒体快速前进/后退到相应的位置。
3.播放视频时，可全屏显示/退出全屏显示。
4.UI自定。
5.对关键代码要在实验报告里阐释。

Bonus：
1.增加进度条用以调节音量。
2.可手动选择本机上的媒体资源进行播放。

Big Bonus：
播放音乐时，封面绕自身中心不断旋转，直至播放结束，封面复位；
暂停时，封面的旋转动作也暂停；
继续播放，封面也跟着继续旋转；
停止时，封面复位。
播放视频时，隐藏封面。
详情请参照网易云音乐的效果~~
```

### 关于其他的说明

1. 控制栏触发是鼠标在窗口内。
2. 本实验最具含金量的部分应该是自定义按钮样式

### 要求的关键代码

```xml
<!--旋转-->
<Storyboard x:Name="Rotate">
      <DoubleAnimation Storyboard.TargetName="Circle"
                               Storyboard.TargetProperty="(Circle.RenderTransform).(CompositeTransform.Rotation)" 
                               To="360" Duration="0:0:30" RepeatBehavior="Forever" />
    </Storyboard>

<!--播放主体部分-->
<MediaElement x:Name="mediaElement"
                  AutoPlay="True"
                  Volume="0.8"
                  MediaOpened="mediaElement_MediaOpened"
                  />


```

```c#
	   public MainPage()
        {
            this.InitializeComponent();
            // 添加事件处理函数
         	mediaElement.CurrentStateChanged += MediaElement_CurrentStateChanged;
            mediaElement.MediaOpened += MediaElement_MediaOpened;
        }

        private void MediaElement_MediaOpened(object sender, RoutedEventArgs e)
        {
          // 初始化值
            positionSlider.Value = 0;
        }

        private void MediaElement_CurrentStateChanged(object sender, RoutedEventArgs e)
        {
          // 改变旋转状态
            switch ((sender as Windows.UI.Xaml.Controls.MediaElement).CurrentState)
            {
                case MediaElementState.Playing:
                    Rotate.Begin();
                    break;
                case MediaElementState.Paused:
                    Rotate.Pause();
                    break;
                default:
                    Rotate.Stop();
                    break;
            }
        }
```

其余千篇一律的控制选单，绑定+事件处理，这里就不贴了。只再补充一点关于Button的样式的代码

```xml
<SolidColorBrush x:Key="ButtonBackgroundColor" Color="{StaticResource SystemChromeLowColor}"/>
  <SolidColorBrush x:Key="ButtonHoverColor" Color="{StaticResource SystemChromeMediumColor}"/>
  <SolidColorBrush x:Key="ButtonHoverLineColor" Color="{StaticResource SystemChromeBlackMediumColor}"/>

  <Style x:Key="Button" TargetType="Button">
    <Setter Property="Width" Value="48"/>
    <Setter Property="Height" Value="48"/>
    <Setter Property="Template">
      <Setter.Value>
        <ControlTemplate TargetType="Button">
          <Grid Background="{StaticResource ButtonBackgroundColor}" x:Name="ButtonGrid">
            <VisualStateManager.VisualStateGroups>
              <VisualStateGroup x:Name="CommonStates">
                <VisualState x:Name="Normal"/>
                <VisualState x:Name="PointerOver">
                  <Storyboard>
                  <ObjectAnimationUsingKeyFrames 
                         Storyboard.TargetName="ButtonHoverLine" Storyboard.TargetProperty="Opacity">
                    <DiscreteObjectKeyFrame KeyTime="0" Value="1"/>
                  </ObjectAnimationUsingKeyFrames>
                    <ObjectAnimationUsingKeyFrames 
                         Storyboard.TargetName="ButtonGrid" Storyboard.TargetProperty="Background">
                      <DiscreteObjectKeyFrame KeyTime="0" Value="{StaticResource ButtonHoverColor}"/>
                    </ObjectAnimationUsingKeyFrames>
                  </Storyboard>
                </VisualState>
                <VisualState x:Name="Pressed"/>
              </VisualStateGroup>
            </VisualStateManager.VisualStateGroups>
            <!--<Ellipse x:Name="Ellipse" Fill="{TemplateBinding Background}"/>-->
            <Rectangle x:Name="ButtonHoverLine" Fill="{StaticResource ButtonHoverLineColor}"
                       Height="4" HorizontalAlignment="Stretch" VerticalAlignment="Bottom" Opacity="0"/>
            <ContentPresenter HorizontalAlignment="Center" VerticalAlignment="Center"/>
          </Grid>
        </ControlTemplate>
      </Setter.Value>
    </Setter>
  </Style>
```

