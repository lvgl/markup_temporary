#include "hello.hpp"
#include "animation_definitions.h"
#include "json_to_language.h"
#include "bissell_colors.h"
#include "bissell_text_styles.h"
#include "cJSON.h"
#include "arc_animation_factory.h"
#include "bar_animation_factory.h"
#include "image_animation_factory.h"
#include "label_animation_factory.h"
#include "meter_animation_factory.h"
#include "object_animation_factory.h"
#include "lottie_animation_factory.h"
#include "utility_animation_factory.h"
#include "data_model.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "dm_key_definitions.h"
#include "dm_key_events.hpp"
#include "cleaning.hpp"
#include "pairing_guide_1.hpp"
// ----------------------------------------------------------------------------
// State: HELLO
//

void HELLO::entry()
{
	LV_LOG_USER("Public View Class HELLO Entry at %lld", VIEW_TIMER());
	setViewCreationTime(VIEW_TIMER());
	incrementTimesLoaded();

	LV_LOG_INFO("HELLO Times Loaded: %d", getTimesLoaded());
	HELLO::view = lv_obj_create(NULL);
	lv_obj_set_size(HELLO::view, 240, 320);
	lv_obj_set_scrollbar_mode(HELLO::view, 0);
	lv_obj_set_style_bg_opa(HELLO::view, 255, 0);
	const int* view_color_arr = color_enum2rgb((ColorId)COLOR_BLACK);
	lv_obj_set_style_bg_color(HELLO::view, lv_color_make(view_color_arr[0], view_color_arr[1], view_color_arr[2]), 0);


	lv_scr_load_anim(HELLO::view, LV_SCR_LOAD_ANIM_NONE, 0, 0, true);
	HELLO::build_widget_0();
	HELLO::build_widget_1();
	HELLO::build_widget_2();
}

void HELLO::exit()
{
	LV_LOG_USER("Public View Class HELLO Exit at %lld", VIEW_TIMER());
}

void HELLO::react(TransitByIdEvent const & e)
{
	LV_LOG_USER("HELLO::react TransitByIdEvent at %lld with transit for %d", VIEW_TIMER(), e.next_view_id);
	switch (e.next_view_id) {
		case VIEW_TYPE_CLEANING:
			transit<CLEANING>();
			break;
		case VIEW_TYPE_PAIRING_GUIDE_1:
			transit<PAIRING_GUIDE_1>();
			break;
	}
}

static void TearDownCompleteCb(lv_timer_t * timer) {
	int * next_view = (int*)timer->user_data;
	LV_LOG_INFO("HELLO TearDownCompleteCb at %lld with transit for %d", VIEW_TIMER(), *next_view);
	TransitByIdEvent transit_event;
	transit_event.next_view_id = *next_view;
	send_tinyfsm_event(transit_event);
	lv_timer_del(timer);
}

void HELLO::react(TearDownEvent const & e)
{
	LV_LOG_INFO("Public View Class HELLO TearDown at %lld", VIEW_TIMER());
	uint16_t longest_exit_anim = 0;
	uint16_t temp = 0;
	temp = HELLO::destroy_widget_0();
	if (temp > longest_exit_anim) { longest_exit_anim = temp; }
	temp = HELLO::destroy_widget_1();
	if (temp > longest_exit_anim) { longest_exit_anim = temp; }
	temp = HELLO::destroy_widget_2();
	if (temp > longest_exit_anim) { longest_exit_anim = temp; }
	int * next_view = (int*)heap_caps_malloc(sizeof(int), MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
	memcpy(next_view, &(e.view_id), sizeof(int));
	lv_timer_t * teardown_timer = lv_timer_create(TearDownCompleteCb, longest_exit_anim, next_view);
}

void HELLO::react(DurableStateISCLEANINGEvent const & e)
{
	LV_LOG_USER("Received a DurableStateISCLEANINGEvent\n");
	LV_LOG_INFO("Checking possible transit to CLEANING\n");

	uint16_t CLEANING_transition_trigger = 0;

	if (get_data(DURABLE_STATE_ISCLEANING) == 1) {
		CLEANING_transition_trigger |= 1 <<0;
	}
	else {
		CLEANING_transition_trigger &= ~(1<<0);
	}

	if (CLEANING_transition_trigger == 1) {
		LV_LOG_USER("Trigger to transition to CLEANING from HELLO is true");
		TearDownEvent tear_down_event;
		tear_down_event.view_id = VIEW_TYPE_CLEANING;
		send_tinyfsm_event(tear_down_event);
	}
	else {
		LV_LOG_INFO("Trigger to transition to CLEANING from HELLO is false\n");
	}

}

void HELLO::react(TimeoutEvent const & e)
{
	setCurrentTime(e.current_time);
	LV_LOG_USER("Received a TimeoutEvent\n");
	LV_LOG_INFO("Checking possible transit to PAIRING_GUIDE_1\n");

	uint16_t PAIRING_GUIDE_1_transition_trigger = 0;

	if (view_creation_time + 3500 <= getCurrentTime()) {
		PAIRING_GUIDE_1_transition_trigger |= 1 <<0;
	}
	else {
		PAIRING_GUIDE_1_transition_trigger &= ~(1<<0);
	}

	if (PAIRING_GUIDE_1_transition_trigger == 1) {
		LV_LOG_USER("Trigger to transition to PAIRING_GUIDE_1 from HELLO is true");
		TearDownEvent tear_down_event;
		tear_down_event.view_id = VIEW_TYPE_PAIRING_GUIDE_1;
		send_tinyfsm_event(tear_down_event);
	}
	else {
		LV_LOG_INFO("Trigger to transition to PAIRING_GUIDE_1 from HELLO is false\n");
	}

}

void HELLO::build_widget_0() {
	HELLO::view_widgets[0] = lv_obj_create(HELLO::view);
	lv_obj_set_scrollbar_mode(HELLO::view_widgets[0], LV_SCROLLBAR_MODE_OFF);
	struct obj_anim_info_t* widget_0_anim_info = (struct obj_anim_info_t*)malloc(sizeof(struct obj_anim_info_t));
	lv_obj_align(HELLO::view_widgets[0], LV_ALIGN_TOP_MID, (lv_coord_t)0, (lv_coord_t)40);
	widget_0_anim_info->cur_alignment = LV_ALIGN_TOP_MID;
	widget_0_anim_info->cur_x_offs = 0;
	widget_0_anim_info->cur_y_offs = 40;
	widget_0_anim_info->state = 0;
	widget_0_anim_info->repeat_count = 0;
	lv_obj_set_user_data(HELLO::view_widgets[0], (void*)widget_0_anim_info);
	const int* widget_0_object_color_arr = color_enum2rgb((ColorId)COLOR_GREY);
	lv_obj_set_style_bg_color(HELLO::view_widgets[0], lv_color_make(widget_0_object_color_arr[0], widget_0_object_color_arr[1], widget_0_object_color_arr[2]), LV_PART_MAIN);
	lv_obj_set_width(HELLO::view_widgets[0], 140);
	lv_obj_set_height(HELLO::view_widgets[0], 140);
	lv_obj_set_style_radius(HELLO::view_widgets[0], LV_RADIUS_CIRCLE, LV_PART_MAIN);
	lv_obj_set_style_border_width(HELLO::view_widgets[0], 0, LV_PART_MAIN);

	if (1) {
		LV_LOG_INFO("Setting Anim for bg_opa, from 0 to 255 over 500 ms");
		lv_anim_t anim_bg_opa_widget_0_0 = set_bg_opa(HELLO::view_widgets[0], 0, 255, 500, 0, lv_anim_path_ease_in_out);
		lv_anim_start(&anim_bg_opa_widget_0_0);

	}
}

uint16_t HELLO::destroy_widget_0() {
	return 10;
}

void HELLO::build_widget_1() {
	HELLO::view_widgets[1] = lv_img_create(HELLO::view_widgets[0]);
	lv_obj_set_scrollbar_mode(HELLO::view_widgets[1], LV_SCROLLBAR_MODE_OFF);
	struct obj_anim_info_t* widget_1_anim_info = (struct obj_anim_info_t*)malloc(sizeof(struct obj_anim_info_t));
	lv_obj_align(HELLO::view_widgets[1], LV_ALIGN_CENTER, (lv_coord_t)0, (lv_coord_t)0);
	widget_1_anim_info->cur_alignment = LV_ALIGN_CENTER;
	widget_1_anim_info->cur_x_offs = 0;
	widget_1_anim_info->cur_y_offs = 0;
	widget_1_anim_info->state = 0;
	widget_1_anim_info->repeat_count = 0;
	lv_obj_set_user_data(HELLO::view_widgets[1], (void*)widget_1_anim_info);
	LV_IMG_DECLARE(hand);
	lv_img_set_src(HELLO::view_widgets[1], &hand);
	lv_img_set_angle(HELLO::view_widgets[1], 3599);


	if (1) {
		LV_LOG_INFO("Setting Anim for img_opa, from 0 to 255 over 500 ms");
		lv_anim_t anim_img_opa_widget_1_0 = set_img_opa(HELLO::view_widgets[1], 0, 255, 500, 0, lv_anim_path_ease_in_out);
		lv_anim_start(&anim_img_opa_widget_1_0);

	}

	if (1) {
		LV_LOG_INFO("Setting Anim for img_rotation, from 3599 to 3100 over 250 ms");
		lv_anim_t anim_img_rotation_widget_1_1 = set_img_rotate(HELLO::view_widgets[1], 3599, 3100, 250, 750, lv_anim_path_ease_in_out);
		if (1) {
			static lv_anim_t anim_img_rotation_widget_1_ready = set_img_rotate(HELLO::view_widgets[1], 3100, 3599, 250, 0, lv_anim_path_ease_in_out);
			lv_anim_set_user_data(&anim_img_rotation_widget_1_1, &anim_img_rotation_widget_1_ready);
			lv_anim_set_ready_cb(&anim_img_rotation_widget_1_1, &generic_ready_cb);
		}
		lv_anim_start(&anim_img_rotation_widget_1_1);

	}
}

uint16_t HELLO::destroy_widget_1() {

	if (1) {
		LV_LOG_INFO("Setting Anim for pos_x, from c to -30 over 250 ms");
		lv_anim_t anim_pos_x_widget_1_0 = set_pos_x(HELLO::view_widgets[1], ((struct obj_anim_info_t *)lv_obj_get_user_data(HELLO::view_widgets[1]))->cur_x_offs, -30, 250, 0, lv_anim_path_ease_in_out);
		lv_anim_start(&anim_pos_x_widget_1_0);

	}

	if (1) {
		LV_LOG_INFO("Setting Anim for img_opa, from c to 0 over 250 ms");
		lv_anim_t anim_img_opa_widget_1_1 = set_img_opa(HELLO::view_widgets[1], lv_obj_get_style_img_opa(HELLO::view_widgets[1], 0), 0, 250, 0, lv_anim_path_ease_in_out);
		lv_anim_start(&anim_img_opa_widget_1_1);

	}
	return 260;
}

void HELLO::build_widget_2() {
	HELLO::view_widgets[2] = lv_label_create(HELLO::view);
	lv_obj_set_scrollbar_mode(HELLO::view_widgets[2], LV_SCROLLBAR_MODE_OFF);
	struct obj_anim_info_t* widget_2_anim_info = (struct obj_anim_info_t*)malloc(sizeof(struct obj_anim_info_t));
	lv_obj_align(HELLO::view_widgets[2], LV_ALIGN_BOTTOM_MID, (lv_coord_t)0, (lv_coord_t)0);
	widget_2_anim_info->cur_alignment = LV_ALIGN_BOTTOM_MID;
	widget_2_anim_info->cur_x_offs = 0;
	widget_2_anim_info->cur_y_offs = 0;
	widget_2_anim_info->state = 0;
	widget_2_anim_info->repeat_count = 0;
	lv_obj_set_user_data(HELLO::view_widgets[2], (void*)widget_2_anim_info);
	lv_label_set_long_mode(HELLO::view_widgets[2], LV_LABEL_LONG_WRAP);
	lv_label_set_recolor(HELLO::view_widgets[2], true);
	lv_obj_set_style_text_font(HELLO::view_widgets[2], get_font_to_use((FontType)FONT_MEDIUM), 0);
	const int* widget_2_text_style_color_arr = color_enum2rgb(get_color_id((FontType)FONT_MEDIUM));
	lv_obj_set_style_text_color(HELLO::view_widgets[2], lv_color_make(widget_2_text_style_color_arr[0], widget_2_text_style_color_arr[1], widget_2_text_style_color_arr[2]), 0);
	lv_obj_set_style_text_opa(HELLO::view_widgets[2], 0, 0);
	if (cJSON_HasObjectItem(language_arr[current_language], "strings"))
	{
		cJSON* strings = cJSON_GetObjectItem(language_arr[current_language], "strings");
		if (cJSON_IsObject(strings))
		{
			cJSON* string_to_use = cJSON_GetObjectItem(strings, "hello");
			if (cJSON_IsString(string_to_use))
			{
				lv_label_set_text_fmt(HELLO::view_widgets[2], string_to_use->valuestring);
			}
		}
	}
	else
	{
		lv_label_set_text_fmt(HELLO::view_widgets[2], "json_string_no_load");
	}

	lv_obj_set_style_text_align(HELLO::view_widgets[2], LV_TEXT_ALIGN_CENTER, 0);


	if (1) {
		LV_LOG_INFO("Setting Anim for pos_y, from c to -30 over 250 ms");
		lv_anim_t anim_pos_y_widget_2_0 = set_pos_y(HELLO::view_widgets[2], ((struct obj_anim_info_t *)lv_obj_get_user_data(HELLO::view_widgets[2]))->cur_y_offs, -30, 250, 2250, lv_anim_path_ease_in_out);
		lv_anim_start(&anim_pos_y_widget_2_0);

	}

	if (1) {
		LV_LOG_INFO("Setting Anim for text_opa, from c to 255 over 250 ms");
		lv_anim_t anim_text_opa_widget_2_1 = set_text_opa(HELLO::view_widgets[2], lv_obj_get_style_text_opa(HELLO::view_widgets[2], 0), 255, 250, 2250, lv_anim_path_ease_in_out);
		lv_anim_start(&anim_text_opa_widget_2_1);

	}
}

uint16_t HELLO::destroy_widget_2() {

	if (1) {
		LV_LOG_INFO("Setting Anim for pos_x, from c to -30 over 250 ms");
		lv_anim_t anim_pos_x_widget_2_0 = set_pos_x(HELLO::view_widgets[2], ((struct obj_anim_info_t *)lv_obj_get_user_data(HELLO::view_widgets[2]))->cur_x_offs, -30, 250, 0, lv_anim_path_ease_in_out);
		lv_anim_start(&anim_pos_x_widget_2_0);

	}

	if (1) {
		LV_LOG_INFO("Setting Anim for text_opa, from c to 0 over 250 ms");
		lv_anim_t anim_text_opa_widget_2_1 = set_text_opa(HELLO::view_widgets[2], lv_obj_get_style_text_opa(HELLO::view_widgets[2], 0), 0, 250, 0, lv_anim_path_ease_in_out);
		lv_anim_start(&anim_text_opa_widget_2_1);

	}
	return 260;
}

