# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: example.proto
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\rexample.proto\x12\x07\x65xample\"\x1b\n\x08Greeting\x12\x0f\n\x07message\x18\x01 \x01(\t2;\n\x07Greeter\x12\x30\n\x08SayHello\x12\x11.example.Greeting\x1a\x11.example.Greetingb\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'example_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:

  DESCRIPTOR._options = None
  _globals['_GREETING']._serialized_start=26
  _globals['_GREETING']._serialized_end=53
  _globals['_GREETER']._serialized_start=55
  _globals['_GREETER']._serialized_end=114
# @@protoc_insertion_point(module_scope)
