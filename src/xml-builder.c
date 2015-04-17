/* xml-builder.c generated by valac 0.14.2, the Vala compiler
 * generated from xml-builder.vala, do not modify */

/* Copyright (c) 2014, CableLabs, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>
#include <gobject/gvaluecollector.h>


#define TYPE_XML_BUILDER (xml_builder_get_type ())
#define XML_BUILDER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_XML_BUILDER, XMLBuilder))
#define XML_BUILDER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_XML_BUILDER, XMLBuilderClass))
#define IS_XML_BUILDER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_XML_BUILDER))
#define IS_XML_BUILDER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_XML_BUILDER))
#define XML_BUILDER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_XML_BUILDER, XMLBuilderClass))

typedef struct _XMLBuilder XMLBuilder;
typedef struct _XMLBuilderClass XMLBuilderClass;
typedef struct _XMLBuilderPrivate XMLBuilderPrivate;
#define _g_string_free0(var) ((var == NULL) ? NULL : (var = (g_string_free (var, TRUE), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))
typedef struct _ParamSpecXMLBuilder ParamSpecXMLBuilder;

struct _XMLBuilder {
	GTypeInstance parent_instance;
	volatile int ref_count;
	XMLBuilderPrivate * priv;
};

struct _XMLBuilderClass {
	GTypeClass parent_class;
	void (*finalize) (XMLBuilder *self);
};

struct _XMLBuilderPrivate {
	GString* builder;
};

struct _ParamSpecXMLBuilder {
	GParamSpec parent_instance;
};


static gpointer xml_builder_parent_class = NULL;

gpointer xml_builder_ref (gpointer instance);
void xml_builder_unref (gpointer instance);
GParamSpec* param_spec_xml_builder (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void value_set_xml_builder (GValue* value, gpointer v_object);
void value_take_xml_builder (GValue* value, gpointer v_object);
gpointer value_get_xml_builder (const GValue* value);
GType xml_builder_get_type (void) G_GNUC_CONST;
#define XML_BUILDER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), TYPE_XML_BUILDER, XMLBuilderPrivate))
enum  {
	XML_BUILDER_DUMMY_PROPERTY
};
XMLBuilder* xml_builder_new (void);
XMLBuilder* xml_builder_construct (GType object_type);
void xml_builder_open_tag (XMLBuilder* self, const gchar* tag, const gchar* attributes);
void xml_builder_close_tag (XMLBuilder* self, const gchar* tag);
void xml_builder_append_node (XMLBuilder* self, const gchar* tag, const gchar* content, const gchar* attributes);
gchar* xml_builder_to_string (XMLBuilder* self);
static void xml_builder_finalize (XMLBuilder* obj);


XMLBuilder* xml_builder_construct (GType object_type) {
	XMLBuilder* self = NULL;
	GString* _tmp0_;
	self = (XMLBuilder*) g_type_create_instance (object_type);
	_tmp0_ = g_string_new ("");
	_g_string_free0 (self->priv->builder);
	self->priv->builder = _tmp0_;
	return self;
}


XMLBuilder* xml_builder_new (void) {
	return xml_builder_construct (TYPE_XML_BUILDER);
}


void xml_builder_open_tag (XMLBuilder* self, const gchar* tag, const gchar* attributes) {
	GString* _tmp0_;
	const gchar* _tmp1_;
	const gchar* _tmp2_;
	GString* _tmp6_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (tag != NULL);
	_tmp0_ = self->priv->builder;
	_tmp1_ = tag;
	g_string_append_printf (_tmp0_, "<%s", _tmp1_);
	_tmp2_ = attributes;
	if (_tmp2_ != NULL) {
		GString* _tmp3_;
		GString* _tmp4_;
		const gchar* _tmp5_;
		_tmp3_ = self->priv->builder;
		g_string_append_c (_tmp3_, ' ');
		_tmp4_ = self->priv->builder;
		_tmp5_ = attributes;
		g_string_append (_tmp4_, _tmp5_);
	}
	_tmp6_ = self->priv->builder;
	g_string_append_c (_tmp6_, '>');
}


void xml_builder_close_tag (XMLBuilder* self, const gchar* tag) {
	GString* _tmp0_;
	const gchar* _tmp1_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (tag != NULL);
	_tmp0_ = self->priv->builder;
	_tmp1_ = tag;
	g_string_append_printf (_tmp0_, "</%s>", _tmp1_);
}


void xml_builder_append_node (XMLBuilder* self, const gchar* tag, const gchar* content, const gchar* attributes) {
	const gchar* _tmp0_;
	const gchar* _tmp1_;
	GString* _tmp2_;
	const gchar* _tmp3_;
	gchar* _tmp4_ = NULL;
	gchar* _tmp5_;
	const gchar* _tmp6_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (tag != NULL);
	g_return_if_fail (content != NULL);
	_tmp0_ = tag;
	_tmp1_ = attributes;
	xml_builder_open_tag (self, _tmp0_, _tmp1_);
	_tmp2_ = self->priv->builder;
	_tmp3_ = content;
	_tmp4_ = g_markup_escape_text (_tmp3_, (gssize) (-1));
	_tmp5_ = _tmp4_;
	g_string_append (_tmp2_, _tmp5_);
	_g_free0 (_tmp5_);
	_tmp6_ = tag;
	xml_builder_close_tag (self, _tmp6_);
}


gchar* xml_builder_to_string (XMLBuilder* self) {
	gchar* result = NULL;
	GString* _tmp0_;
	const gchar* _tmp1_;
	gchar* _tmp2_;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = self->priv->builder;
	_tmp1_ = _tmp0_->str;
	_tmp2_ = g_strdup (_tmp1_);
	result = _tmp2_;
	return result;
}


static void value_xml_builder_init (GValue* value) {
	value->data[0].v_pointer = NULL;
}


static void value_xml_builder_free_value (GValue* value) {
	if (value->data[0].v_pointer) {
		xml_builder_unref (value->data[0].v_pointer);
	}
}


static void value_xml_builder_copy_value (const GValue* src_value, GValue* dest_value) {
	if (src_value->data[0].v_pointer) {
		dest_value->data[0].v_pointer = xml_builder_ref (src_value->data[0].v_pointer);
	} else {
		dest_value->data[0].v_pointer = NULL;
	}
}


static gpointer value_xml_builder_peek_pointer (const GValue* value) {
	return value->data[0].v_pointer;
}


static gchar* value_xml_builder_collect_value (GValue* value, guint n_collect_values, GTypeCValue* collect_values, guint collect_flags) {
	if (collect_values[0].v_pointer) {
		XMLBuilder* object;
		object = collect_values[0].v_pointer;
		if (object->parent_instance.g_class == NULL) {
			return g_strconcat ("invalid unclassed object pointer for value type `", G_VALUE_TYPE_NAME (value), "'", NULL);
		} else if (!g_value_type_compatible (G_TYPE_FROM_INSTANCE (object), G_VALUE_TYPE (value))) {
			return g_strconcat ("invalid object type `", g_type_name (G_TYPE_FROM_INSTANCE (object)), "' for value type `", G_VALUE_TYPE_NAME (value), "'", NULL);
		}
		value->data[0].v_pointer = xml_builder_ref (object);
	} else {
		value->data[0].v_pointer = NULL;
	}
	return NULL;
}


static gchar* value_xml_builder_lcopy_value (const GValue* value, guint n_collect_values, GTypeCValue* collect_values, guint collect_flags) {
	XMLBuilder** object_p;
	object_p = collect_values[0].v_pointer;
	if (!object_p) {
		return g_strdup_printf ("value location for `%s' passed as NULL", G_VALUE_TYPE_NAME (value));
	}
	if (!value->data[0].v_pointer) {
		*object_p = NULL;
	} else if (collect_flags & G_VALUE_NOCOPY_CONTENTS) {
		*object_p = value->data[0].v_pointer;
	} else {
		*object_p = xml_builder_ref (value->data[0].v_pointer);
	}
	return NULL;
}


GParamSpec* param_spec_xml_builder (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags) {
	ParamSpecXMLBuilder* spec;
	g_return_val_if_fail (g_type_is_a (object_type, TYPE_XML_BUILDER), NULL);
	spec = g_param_spec_internal (G_TYPE_PARAM_OBJECT, name, nick, blurb, flags);
	G_PARAM_SPEC (spec)->value_type = object_type;
	return G_PARAM_SPEC (spec);
}


gpointer value_get_xml_builder (const GValue* value) {
	g_return_val_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, TYPE_XML_BUILDER), NULL);
	return value->data[0].v_pointer;
}


void value_set_xml_builder (GValue* value, gpointer v_object) {
	XMLBuilder* old;
	g_return_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, TYPE_XML_BUILDER));
	old = value->data[0].v_pointer;
	if (v_object) {
		g_return_if_fail (G_TYPE_CHECK_INSTANCE_TYPE (v_object, TYPE_XML_BUILDER));
		g_return_if_fail (g_value_type_compatible (G_TYPE_FROM_INSTANCE (v_object), G_VALUE_TYPE (value)));
		value->data[0].v_pointer = v_object;
		xml_builder_ref (value->data[0].v_pointer);
	} else {
		value->data[0].v_pointer = NULL;
	}
	if (old) {
		xml_builder_unref (old);
	}
}


void value_take_xml_builder (GValue* value, gpointer v_object) {
	XMLBuilder* old;
	g_return_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, TYPE_XML_BUILDER));
	old = value->data[0].v_pointer;
	if (v_object) {
		g_return_if_fail (G_TYPE_CHECK_INSTANCE_TYPE (v_object, TYPE_XML_BUILDER));
		g_return_if_fail (g_value_type_compatible (G_TYPE_FROM_INSTANCE (v_object), G_VALUE_TYPE (value)));
		value->data[0].v_pointer = v_object;
	} else {
		value->data[0].v_pointer = NULL;
	}
	if (old) {
		xml_builder_unref (old);
	}
}


static void xml_builder_class_init (XMLBuilderClass * klass) {
	xml_builder_parent_class = g_type_class_peek_parent (klass);
	XML_BUILDER_CLASS (klass)->finalize = xml_builder_finalize;
	g_type_class_add_private (klass, sizeof (XMLBuilderPrivate));
}


static void xml_builder_instance_init (XMLBuilder * self) {
	self->priv = XML_BUILDER_GET_PRIVATE (self);
	self->ref_count = 1;
}


static void xml_builder_finalize (XMLBuilder* obj) {
	XMLBuilder * self;
	self = XML_BUILDER (obj);
	_g_string_free0 (self->priv->builder);
}


GType xml_builder_get_type (void) {
	static volatile gsize xml_builder_type_id__volatile = 0;
	if (g_once_init_enter (&xml_builder_type_id__volatile)) {
		static const GTypeValueTable g_define_type_value_table = { value_xml_builder_init, value_xml_builder_free_value, value_xml_builder_copy_value, value_xml_builder_peek_pointer, "p", value_xml_builder_collect_value, "p", value_xml_builder_lcopy_value };
		static const GTypeInfo g_define_type_info = { sizeof (XMLBuilderClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) xml_builder_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (XMLBuilder), 0, (GInstanceInitFunc) xml_builder_instance_init, &g_define_type_value_table };
		static const GTypeFundamentalInfo g_define_type_fundamental_info = { (G_TYPE_FLAG_CLASSED | G_TYPE_FLAG_INSTANTIATABLE | G_TYPE_FLAG_DERIVABLE | G_TYPE_FLAG_DEEP_DERIVABLE) };
		GType xml_builder_type_id;
		xml_builder_type_id = g_type_register_fundamental (g_type_fundamental_next (), "XMLBuilder", &g_define_type_info, &g_define_type_fundamental_info, 0);
		g_once_init_leave (&xml_builder_type_id__volatile, xml_builder_type_id);
	}
	return xml_builder_type_id__volatile;
}


gpointer xml_builder_ref (gpointer instance) {
	XMLBuilder* self;
	self = instance;
	g_atomic_int_inc (&self->ref_count);
	return instance;
}


void xml_builder_unref (gpointer instance) {
	XMLBuilder* self;
	self = instance;
	if (g_atomic_int_dec_and_test (&self->ref_count)) {
		XML_BUILDER_GET_CLASS (self)->finalize (self);
		g_type_free_instance ((GTypeInstance *) self);
	}
}


