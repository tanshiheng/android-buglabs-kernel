/*
 * Generic panel support
 *
 * Copyright (C) 2008 Nokia Corporation
 * Author: Tomi Valkeinen <tomi.valkeinen@nokia.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <linux/module.h>
#include <linux/delay.h>
#include <mach/display.h>

static struct omap_video_timings generic_panel_timings = {
	/* 1280 x 1024 @ 57 Hz */
        
  	.x_res		= 1280,
  	.y_res		= 1024,
	.pixel_clock	= 86400,
	.hfp		= 80,
	.hbp		= 48,
	.hsw		= 32,
	.vfp		= 3,
	.vbp		= 18,
	.vsw		= 7,
	

	/* 1024 x 768 @ 57 Hz */        
	/*
  	.x_res		= 1024,
  	.y_res		= 768,
	.pixel_clock	= 63500,
	.hfp		= 23,
	.hbp		= 159,
	.hsw		= 135,
	.vfp		= 2,
	.vbp		= 28,
	.vsw		= 5,
	*/
   	/* 800 x 600 */
	/*
  	.x_res		= 800,
  	.y_res		= 600,
	.pixel_clock	= 40000,
	.hfp		= 40,
	.hbp		= 88,
	.hsw		= 128,
	.vfp		= 1,
	.vbp		= 23,
	.vsw		= 4,
	//Hsync polarity: +
	//Vsync polarity: +
	*/
	
	/* 640 x 480 @ 60 Hz  Reduced blanking VESA CVT 0.31M3-R */        
	/*
	.x_res          = 640,
	.y_res          = 480,
	.pixel_clock	= 23500,
	.hfp		= 48,
	.hbp		= 80,
	.hsw		= 32,
	.vfp		= 3,
	.vbp		= 7,
	.vsw		= 4,
	*/
};

static int generic_panel_probe(struct omap_dss_device *dssdev)
{
	dssdev->panel.config = OMAP_DSS_LCD_TFT;
	dssdev->panel.timings = generic_panel_timings;

	return 0;
}

static void generic_panel_remove(struct omap_dss_device *dssdev)
{
}

static int generic_panel_enable(struct omap_dss_device *dssdev)
{
	int r = 0;

	if (dssdev->platform_enable)
		r = dssdev->platform_enable(dssdev);

	return r;
}

static void generic_panel_disable(struct omap_dss_device *dssdev)
{
	if (dssdev->platform_disable)
		dssdev->platform_disable(dssdev);
}

static int generic_panel_suspend(struct omap_dss_device *dssdev)
{
	generic_panel_disable(dssdev);
	return 0;
}

static int generic_panel_resume(struct omap_dss_device *dssdev)
{
	return generic_panel_enable(dssdev);
}

static struct omap_dss_driver generic_driver = {
	.probe		= generic_panel_probe,
	.remove		= generic_panel_remove,

	.enable		= generic_panel_enable,
	.disable	= generic_panel_disable,
	.suspend	= generic_panel_suspend,
	.resume		= generic_panel_resume,

	.driver         = {
		.name   = "generic_panel",
		.owner  = THIS_MODULE,
	},
};

static int __init generic_panel_drv_init(void)
{
	return omap_dss_register_driver(&generic_driver);
}

static void __exit generic_panel_drv_exit(void)
{
	omap_dss_unregister_driver(&generic_driver);
}

module_init(generic_panel_drv_init);
module_exit(generic_panel_drv_exit);
MODULE_LICENSE("GPL");
