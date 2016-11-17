#include <rtthread.h>

#include <rtgui/rtgui.h>
#include <rtgui/rtgui_app.h>
#include <rtgui/widgets/window.h>
#include <rtgui/widgets/label.h>
#include <rtgui/driver.h>

/* ��LCD�ϴ���һ�������ڣ����ǵ�һ������ */
static void win_thread_entry(void *parameter)
{
    struct rtgui_app *app;
    struct rtgui_win *win;
    struct rtgui_label *label;
    struct rtgui_rect rect;

    app = rtgui_app_create(rt_thread_self(), "MyApp");
    RT_ASSERT(app != RT_NULL);

    /* create a full screen window */
    rtgui_graphic_driver_get_rect(rtgui_graphic_driver_get_default(), &rect);

    win = rtgui_win_create(RT_NULL, "MainWin", &rect,
                           RTGUI_WIN_STYLE_NO_BORDER | RTGUI_WIN_STYLE_NO_TITLE);
    if (win == RT_NULL)
    {
        rtgui_app_destroy(app);
        return;
    }

    /* ����һ��label������Ϊhelloworld */
    label = rtgui_label_create("Hello World!");

    /* ����label��λ�ã������Ǿ������� */
	rect.x1 = 0;
	rect.y1 = 100;
	rect.x2 = 240;
	rect.y2 = 140;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);

	rt_kprintf("bc: %x\n", RTGUI_WIDGET_BACKGROUND(label));
	rt_kprintf("fc: %x\n", RTGUI_WIDGET_FOREGROUND(label));
#if 0
	RTGUI_WIDGET_BACKGROUND(label) = 0;
	RTGUI_WIDGET_FOREGROUND(label) = RTGUI_RGB(0xFF, 0xFF, 0);
#endif

    /*���label��������*/
    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(label));

    /* ��ʾ������ */
    rtgui_win_show(win, RT_FALSE);

    /* ѭ�� */
    rtgui_app_run(app);

    rtgui_win_destroy(win);
    rtgui_app_destroy(app);
    rt_kprintf("MyApp Quit.\n");
}

int main()
{
    rt_thread_t tid;

    tid = rt_thread_create("win", win_thread_entry, RT_NULL,
                           2048, 20, 20);
    if (tid != RT_NULL)
    {
        rt_thread_startup(tid);
    }

    return 0;
}
