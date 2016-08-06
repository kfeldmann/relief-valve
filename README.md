rv: A relief valve for pipelines
================================

You might have pipelines in your infrastructure, and once in a while
a component in the pipeline might block, and stop the whole pipeline.

It might be nice to buffer the stream until the downstream component
unblocks so that upstream services can keep doing their jobs. In fact,
depending on the service, it might even be more valuable to throw data
away rather than to stop the upstream service (e.g. maybe the service
is a critical web application and the data stream that is blocking is
just for analytics, etc.).

Rv does three things:

- It will buffer data for a while and then write
  it downstream as soon as it can
- It will send error messages on a different channel
  when the downstream is blocking
- It will continue reading from upstream no matter
  what, even if it means throwing that data away
  (e.g. if the downstream is still blocking and the
  internal buffer is full)

General usage:

```
    +-----------------+           +-----------------+
    |                 |           |                 |
    |   upstream      |           |   downstream    |
    |    service      |  +-----+  |    service      |
    |   producing     |->| rv  |->|   consuming     |
    |     data        |  +--+--+  |      data       |
    |                 |     |     |                 |
    +-----------------+     |     +-----------------+
                            |
                     +------v------+
                     |             |
                     |    error    |
                     |  handling   |
                     |   service   |
                     |             |
                     +------+------+
```
