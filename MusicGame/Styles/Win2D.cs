/*
 * 描 述：页面特效静态类，用于实现高斯模糊特效
 */

using Microsoft.Graphics.Canvas.Effects;
using Windows.UI;
using Windows.UI.Composition;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Hosting;

namespace MoePicture_Yande.Styles
{
    /// <summary>
    /// 页面特效静态类，用于实现高斯模糊特效
    /// </summary>
    public class Win2D
    {
        public static void initialBackground(UIElement glass)
        {
            Visual hostVisual = ElementCompositionPreview.GetElementVisual(glass);
            Compositor compositor = hostVisual.Compositor;
            try
            {
                var backdropBrush = compositor.CreateHostBackdropBrush();
                var glassVisual = compositor.CreateSpriteVisual();
                // glassVisual.Size = hostVisual.Size;

                glassVisual.Brush = backdropBrush;
                ElementCompositionPreview.SetElementChildVisual(glass, glassVisual);

                var bindSizeAnimation = compositor.CreateExpressionAnimation("hostVisual.Size");
                bindSizeAnimation.SetReferenceParameter("hostVisual", hostVisual);
                glassVisual.StartAnimation("Size", bindSizeAnimation);
            }
            catch
            {
                // for phone's no CreateHostBackdropBrush
            }
        }

        public static void initialPane(UIElement glass)
        {
            Visual hostVisual = ElementCompositionPreview.GetElementVisual(glass);
            Compositor compositor = hostVisual.Compositor;

            var glassEffect = new GaussianBlurEffect
            {
                BlurAmount = 1.0f,
                BorderMode = EffectBorderMode.Hard,
                Source = new ArithmeticCompositeEffect
                {
                    MultiplyAmount = 0,
                    Source1Amount = 0.2f,
                    Source2Amount = 0.8f,
                    Source1 = new CompositionEffectSourceParameter("backdropBrush"),
                    Source2 = new ColorSourceEffect
                    {
                        Color = Color.FromArgb(230, 230, 230, 230)
                    }
                }
            };
            var effectFactory = compositor.CreateEffectFactory(glassEffect);
            try
            {
                var backdropBrush = compositor.CreateHostBackdropBrush();
                var effectBrush = effectFactory.CreateBrush();
                effectBrush.SetSourceParameter("backdropBrush", backdropBrush);

                var glassVisual = compositor.CreateSpriteVisual();
                glassVisual.Brush = effectBrush;

                ElementCompositionPreview.SetElementChildVisual(glass, glassVisual);

                var bindSizeAnimation = compositor.CreateExpressionAnimation("hostVisual.Size");
                bindSizeAnimation.SetReferenceParameter("hostVisual", hostVisual);
                glassVisual.StartAnimation("Size", bindSizeAnimation);
            }
            catch
            {
                // for phones no CreateHostBackdropBrush();
            }
        }

        public static void initialGlass(UIElement glass)
        {
            Visual hostVisual = ElementCompositionPreview.GetElementVisual(glass);
            Compositor compositor = hostVisual.Compositor;

            var glassEffect = new GaussianBlurEffect
            {
                BlurAmount = 15.0f,
                BorderMode = EffectBorderMode.Hard,
                Source = new ArithmeticCompositeEffect
                {
                    MultiplyAmount = 0,
                    Source1Amount = 0.5f,
                    Source2Amount = 0.5f,
                    Source1 = new CompositionEffectSourceParameter("backdropBrush"),
                    Source2 = new ColorSourceEffect
                    {
                        Color = Color.FromArgb(255, 245, 245, 245)
                    }
                }
            };
            var effectFactory = compositor.CreateEffectFactory(glassEffect);

            var backdropBrush = compositor.CreateBackdropBrush();
            var effectBrush = effectFactory.CreateBrush();
            effectBrush.SetSourceParameter("backdropBrush", backdropBrush);

            var glassVisual = compositor.CreateSpriteVisual();
            glassVisual.Brush = effectBrush;

            ElementCompositionPreview.SetElementChildVisual(glass, glassVisual);

            var bindSizeAnimation = compositor.CreateExpressionAnimation("hostVisual.Size");
            bindSizeAnimation.SetReferenceParameter("hostVisual", hostVisual);
            glassVisual.StartAnimation("Size", bindSizeAnimation);
        }
    }
}
