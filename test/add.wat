(module
  (type (;0;) (func (param i32) (result i32)))
  (type (;1;) (func (param i32 i32) (result i32)))
  (import "env" "__linear_memory" (memory (;0;) 0))
  (import "env" "__indirect_function_table" (table (;0;) 0 funcref))
  (export "__main_argc_argv" (func 1))
  (func (;0;) (type 0) (param i32) (result i32)
    local.get 0
    i32.load8_s
    i32.const -48
    i32.add)
  (func (;1;) (type 1) (param i32 i32) (result i32)
    local.get 1
    i32.load offset=4
    i32.load8_s
    local.get 1
    i32.load offset=8
    i32.load8_s
    i32.add
    i32.const -96
    i32.add))
