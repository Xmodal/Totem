{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 7,
			"minor" : 3,
			"revision" : 6,
			"architecture" : "x86",
			"modernui" : 1
		}
,
		"rect" : [ 514.0, 104.0, 732.0, 676.0 ],
		"bglocked" : 0,
		"openinpresentation" : 1,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 1,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 1,
		"objectsnaponopen" : 1,
		"statusbarvisible" : 2,
		"toolbarvisible" : 1,
		"lefttoolbarpinned" : 0,
		"toptoolbarpinned" : 0,
		"righttoolbarpinned" : 0,
		"bottomtoolbarpinned" : 0,
		"toolbars_unpinned_last_save" : 0,
		"tallnewobj" : 0,
		"boxanimatetime" : 200,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"description" : "",
		"digest" : "",
		"tags" : "",
		"style" : "",
		"subpatcher_template" : "",
		"boxes" : [ 			{
				"box" : 				{
					"fontsize" : 4.952033,
					"id" : "obj-5",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"patching_rect" : [ 217.0, 435.129822, 19.5, 14.0 ],
					"style" : "",
					"text" : "i"
				}

			}
, 			{
				"box" : 				{
					"fontsize" : 4.0,
					"id" : "obj-21",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 145.25, 398.401001, 34.0, 13.0 ],
					"style" : "",
					"text" : "loadmess 1.5"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial Bold",
					"fontsize" : 9.0,
					"id" : "obj-23",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 262.5, 412.401001, 112.0, 17.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 60.0, 74.401001, 169.0, 17.0 ],
					"style" : "",
					"text" : "post_smoothing_curve",
					"textcolor" : [ 0.862745, 0.870588, 0.878431, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"activebgcolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"activeslidercolor" : [ 0.278431, 0.839216, 1.0, 1.0 ],
					"activetricolor" : [ 0.278431, 0.839216, 1.0, 1.0 ],
					"activetricolor2" : [ 1.0, 1.0, 1.0, 0.301961 ],
					"annotation" : "",
					"appearance" : 1,
					"bordercolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"focusbordercolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"id" : "obj-24",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 215.25, 412.401001, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 11.0, 75.401001, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "gatepct[4]",
							"parameter_shortname" : "gatepct",
							"parameter_type" : 0,
							"parameter_mmax" : 3240.0,
							"parameter_initial" : [ 3240 ],
							"parameter_unitstyle" : 1,
							"parameter_defer" : 1
						}

					}
,
					"textcolor" : [ 0.094118, 0.117647, 0.137255, 1.0 ],
					"tricolor2" : [ 1.0, 1.0, 1.0, 0.301961 ],
					"varname" : "gatepct[4]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-28",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 217.0, 457.401001, 251.0, 22.0 ],
					"style" : "",
					"text" : "prepend /SNN_output/post_smoothing_curve"
				}

			}
, 			{
				"box" : 				{
					"fontsize" : 4.952033,
					"id" : "obj-8",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"patching_rect" : [ 187.0, 345.129822, 19.5, 14.0 ],
					"style" : "",
					"text" : "i"
				}

			}
, 			{
				"box" : 				{
					"fontsize" : 4.0,
					"id" : "obj-17",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 130.25, 323.401001, 31.0, 13.0 ],
					"style" : "",
					"text" : "loadmess 9"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial Bold",
					"fontsize" : 9.0,
					"id" : "obj-18",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 232.5, 322.401001, 112.0, 27.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 60.0, 59.401001, 169.0, 17.0 ],
					"style" : "",
					"text" : "currentSpikedOutputSmoothing",
					"textcolor" : [ 0.862745, 0.870588, 0.878431, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"activebgcolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"activeslidercolor" : [ 0.278431, 0.839216, 1.0, 1.0 ],
					"activetricolor" : [ 0.278431, 0.839216, 1.0, 1.0 ],
					"activetricolor2" : [ 1.0, 1.0, 1.0, 0.301961 ],
					"annotation" : "",
					"appearance" : 1,
					"bordercolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"focusbordercolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"id" : "obj-19",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 185.25, 322.401001, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 11.0, 60.401001, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "gatepct[2]",
							"parameter_shortname" : "gatepct",
							"parameter_type" : 1,
							"parameter_mmax" : 255.0,
							"parameter_initial" : [ 3240 ],
							"parameter_unitstyle" : 0,
							"parameter_defer" : 1
						}

					}
,
					"textcolor" : [ 0.094118, 0.117647, 0.137255, 1.0 ],
					"tricolor2" : [ 1.0, 1.0, 1.0, 0.301961 ],
					"varname" : "gatepct[3]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-20",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 187.0, 367.401001, 311.0, 22.0 ],
					"style" : "",
					"text" : "prepend /SNN_output/current_spiked_output_smoothing"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-3",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 390.5, 646.0, 137.0, 22.0 ],
					"style" : "",
					"text" : "udpsend localhost 7512"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-4",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 390.5, 616.0, 81.0, 22.0 ],
					"style" : "",
					"text" : "r #0-udpsend"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-6",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 210.5, 646.0, 136.0, 22.0 ],
					"style" : "",
					"text" : "udpsend localhost 7511"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-16",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 210.5, 616.0, 81.0, 22.0 ],
					"style" : "",
					"text" : "r #0-udpsend"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-15",
					"maxclass" : "newobj",
					"numinlets" : 5,
					"numoutlets" : 5,
					"outlettype" : [ "", "", "", "", "" ],
					"patching_rect" : [ 57.554688, 72.0, 522.0, 22.0 ],
					"style" : "",
					"text" : "route output_time_window spiked_scalar currentSpikedOutputSmoothing post_smoothing_curve"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-14",
					"index" : 0,
					"maxclass" : "inlet",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 57.554688, 32.0, 30.0, 30.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"fontsize" : 4.952033,
					"id" : "obj-10",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"patching_rect" : [ 172.0, 240.129822, 19.5, 14.0 ],
					"style" : "",
					"text" : "i"
				}

			}
, 			{
				"box" : 				{
					"fontsize" : 4.0,
					"id" : "obj-11",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 115.25, 218.401001, 35.0, 13.0 ],
					"style" : "",
					"text" : "loadmess 120"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial Bold",
					"fontsize" : 9.0,
					"id" : "obj-12",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 219.25, 216.401001, 112.0, 17.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 60.0, 44.401001, 112.0, 17.0 ],
					"style" : "",
					"text" : "spiked_scalar",
					"textcolor" : [ 0.862745, 0.870588, 0.878431, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"activebgcolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"activeslidercolor" : [ 0.278431, 0.839216, 1.0, 1.0 ],
					"activetricolor" : [ 0.278431, 0.839216, 1.0, 1.0 ],
					"activetricolor2" : [ 1.0, 1.0, 1.0, 0.301961 ],
					"annotation" : "",
					"appearance" : 1,
					"bordercolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"focusbordercolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"id" : "obj-13",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 170.25, 217.401001, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 11.0, 45.401001, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "gatepct[1]",
							"parameter_shortname" : "gatepct",
							"parameter_type" : 0,
							"parameter_mmax" : 3240.0,
							"parameter_initial" : [ 3240 ],
							"parameter_unitstyle" : 0,
							"parameter_defer" : 1
						}

					}
,
					"textcolor" : [ 0.094118, 0.117647, 0.137255, 1.0 ],
					"tricolor2" : [ 1.0, 1.0, 1.0, 0.301961 ],
					"varname" : "gatepct[1]"
				}

			}
, 			{
				"box" : 				{
					"fontsize" : 4.952033,
					"id" : "obj-9",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"patching_rect" : [ 142.0, 150.129822, 19.5, 14.0 ],
					"style" : "",
					"text" : "i"
				}

			}
, 			{
				"box" : 				{
					"fontsize" : 4.0,
					"id" : "obj-40",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 85.25, 128.401001, 33.0, 13.0 ],
					"style" : "",
					"text" : "loadmess 10"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial Bold",
					"fontsize" : 9.0,
					"id" : "obj-38",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 189.25, 126.401001, 112.0, 17.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 60.0, 29.401001, 112.0, 17.0 ],
					"style" : "",
					"text" : "output_time_window",
					"textcolor" : [ 0.862745, 0.870588, 0.878431, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"activebgcolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"activeslidercolor" : [ 0.278431, 0.839216, 1.0, 1.0 ],
					"activetricolor" : [ 0.278431, 0.839216, 1.0, 1.0 ],
					"activetricolor2" : [ 1.0, 1.0, 1.0, 0.301961 ],
					"annotation" : "",
					"appearance" : 1,
					"bordercolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"focusbordercolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"id" : "obj-39",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 140.25, 127.401001, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 11.0, 30.401001, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "gatepct[3]",
							"parameter_shortname" : "gatepct",
							"parameter_type" : 0,
							"parameter_mmin" : 1.0,
							"parameter_mmax" : 10000000000.0,
							"parameter_initial" : [ 10.0 ],
							"parameter_unitstyle" : 0,
							"parameter_defer" : 1
						}

					}
,
					"textcolor" : [ 0.094118, 0.117647, 0.137255, 1.0 ],
					"tricolor2" : [ 1.0, 1.0, 1.0, 0.301961 ],
					"varname" : "gatepct[2]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-7",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 172.0, 262.401001, 203.0, 22.0 ],
					"style" : "",
					"text" : "prepend /SNN_output/spiked_scalar"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-22",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 142.0, 171.0, 239.0, 22.0 ],
					"style" : "",
					"text" : "prepend /SNN_output/output_time_window"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-2",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 57.554688, 552.0, 83.0, 22.0 ],
					"style" : "",
					"text" : "s #0-udpsend"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial Bold",
					"fontsize" : 9.0,
					"id" : "obj-27",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 87.554688, 6.910889, 112.0, 17.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 89.0, 8.742615, 81.0, 17.0 ],
					"style" : "",
					"text" : "SNN_output_osc",
					"textcolor" : [ 1.0, 1.0, 1.0, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"angle" : 0.0,
					"background" : 1,
					"bgcolor" : [ 0.367404, 0.389405, 0.430238, 1.0 ],
					"id" : "obj-25",
					"maxclass" : "panel",
					"mode" : 0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 29.852829, 14.033447, 37.0, 5.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 2.949341, 4.3974, 208.550659, 91.003601 ],
					"proportion" : 0.39,
					"rounded" : 0,
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"angle" : 270.0,
					"background" : 1,
					"bgcolor" : [ 0.862745, 0.870588, 0.878431, 0.5 ],
					"border" : 2,
					"bordercolor" : [ 0.65098, 0.666667, 0.662745, 1.0 ],
					"id" : "obj-26",
					"maxclass" : "panel",
					"mode" : 0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 4.0, 6.910889, 12.0, 188.0 ],
					"presentation" : 1,
					"presentation_rect" : [ -0.239624, 0.338165, 215.739624, 98.658203 ],
					"proportion" : 0.39,
					"style" : ""
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 0 ],
					"source" : [ "obj-10", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-13", 0 ],
					"source" : [ "obj-11", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-10", 0 ],
					"source" : [ "obj-13", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-15", 0 ],
					"source" : [ "obj-14", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-13", 0 ],
					"source" : [ "obj-15", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-19", 0 ],
					"source" : [ "obj-15", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-24", 0 ],
					"source" : [ "obj-15", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-39", 0 ],
					"source" : [ "obj-15", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"source" : [ "obj-16", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-19", 0 ],
					"source" : [ "obj-17", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 0 ],
					"source" : [ "obj-19", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"source" : [ "obj-20", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-24", 0 ],
					"source" : [ "obj-21", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"source" : [ "obj-22", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-5", 0 ],
					"source" : [ "obj-24", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"source" : [ "obj-28", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"source" : [ "obj-39", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-3", 0 ],
					"source" : [ "obj-4", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-39", 0 ],
					"source" : [ "obj-40", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-28", 0 ],
					"source" : [ "obj-5", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"source" : [ "obj-7", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-20", 0 ],
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-22", 0 ],
					"source" : [ "obj-9", 0 ]
				}

			}
 ],
		"parameters" : 		{
			"obj-13" : [ "gatepct[1]", "gatepct", 0 ],
			"obj-39" : [ "gatepct[3]", "gatepct", 0 ],
			"obj-19" : [ "gatepct[2]", "gatepct", 0 ],
			"obj-24" : [ "gatepct[4]", "gatepct", 0 ]
		}
,
		"dependency_cache" : [  ],
		"autosave" : 0,
		"styles" : [ 			{
				"name" : "AudioStatus_Menu",
				"default" : 				{
					"bgfillcolor" : 					{
						"type" : "color",
						"color" : [ 0.294118, 0.313726, 0.337255, 1 ],
						"color1" : [ 0.454902, 0.462745, 0.482353, 0.0 ],
						"color2" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
						"angle" : 270.0,
						"proportion" : 0.39,
						"autogradient" : 0
					}

				}
,
				"parentstyle" : "",
				"multi" : 0
			}
 ]
	}

}
