.. i2c documentation master file, created by
   sphinx-quickstart on Tue Jun 26 16:41:46 2018.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Drivers for I2C Communication
=============================
These drivers support I2C devices. They provide a universal I2C interface for sensor communication across hardware architectures.

.. toctree::
   :maxdepth: 2
   :caption: Contents:

Note: in the future these drivers will support Linux **and** firmware devices.


Prerequisites
-------------

- Linux device with an AMG8833 connected via I2C, such as any version of `Forward Loop Zero <https://forward-loop.com/developer.html>`_ with the optional grid-eye infrared.
- (Optional) Docker on the Linux device. We recommend you check out `floop <https://github.com/ForwardLoopLLC/floopcli>`_, our simple, open-source tool for working with embedded Docker on multiple devices at the same time.

Install
-------

You can install the C++ header files for use in your own applications.  

In order to use the drivers with Linux, you need to install some I2C dependencies:

.. code-block:: bash

    sudo apt-get install -y python-smbus python-dev i2c-tools libi2c-dev 

You then need to install the I2C headers, then include them during compilation of your application. Inside of your application folder, you can install the headers:

.. code-block:: bash

    mkdir -p ./floop/i2c/ && \
    wget -O ./floop/i2c/i2c.h https://github.com/ForwardLoopLLC/i2c/blob/master/linux/i2c.h

When you compile your application, make sure to include the path to the driver headers. For example, add `-I./floop/` during compilation. You can then access the drivers by including the i2c header:

.. code-block:: c++

    #include "linux/i2c.h"

Note that you can also use these steps to install the drivers inside of a Docker container.

Example
-------

The example shows the major functionality of the drivers.

.. literalinclude:: ../../example/main.cpp
    :language: c++



API Documentation
-----------------
:doc:`cpp/api`
    Driver interface for I2C 

`Source Code <https://github.com/ForwardLoopLLc/i2c>`_
    Our MIT license lets you use, change, and sell the drivers for free
