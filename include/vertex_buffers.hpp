#pragma once

#include "glad/glad.h"
namespace pop::gfx {
enum class BufferType : GLuint {
    kNone                    = 0,
    kArrayBuffer             = GL_ARRAY_BUFFER,
    kElementArrayBuffer      = GL_ELEMENT_ARRAY_BUFFER,
    kCopyReadBuffer          = GL_COPY_READ_BUFFER,
    kCopyWriteBuffer         = GL_COPY_WRITE_BUFFER,
    kPixelPackBuffer         = GL_PIXEL_PACK_BUFFER,
    kPixelUnpackBuffer       = GL_PIXEL_UNPACK_BUFFER,
    kUniformBuffer           = GL_UNIFORM_BUFFER,
    kShaderStorageBuffer     = GL_SHADER_STORAGE_BUFFER,
    kAtomicCounterBuffer     = GL_ATOMIC_COUNTER_BUFFER,
    kTransformFeedbackBuffer = GL_TRANSFORM_FEEDBACK_BUFFER,
    kTextureBuffer           = GL_TEXTURE_BUFFER,
    kDrawIndirectBuffer      = GL_DRAW_INDIRECT_BUFFER,
    kDispatchIndirectBuffer  = GL_DISPATCH_INDIRECT_BUFFER,
    kQueryBuffer             = GL_QUERY_BUFFER,
    kParameterBuffer         = GL_PARAMETER_BUFFER
};
class VertexBuffer {
   public:
    explicit VertexBuffer();
    ~VertexBuffer();
    // Returns the shader id
    GLuint id() const { return buffer_id_; }
    // Binds this buffer object to the specified target
    void   Bind(BufferType target);
    // calls glBindBuffer with target and then bufferData
    void   BufferData(BufferType target, GLsizeiptr size, const void* data,
                      GLenum usage);

   private:
    GLuint buffer_id_;
};
}  // namespace pop::gfx
