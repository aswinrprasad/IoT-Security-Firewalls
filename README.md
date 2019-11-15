# SECURITY ANALYSIS OF IOT DEVICES

## ABSTRACT
IoT (Internet of Things) is a new paradigm which provides a set of new
services for the next wave of technological innovations. IoT applications are
nearly limitless while enabling seamless integration of the cyber-world with
the physical world. However, despite the enormous efforts of standardization
bodies, alliances, industries, researchers and others, there are still numerous
problems to deal with in order to reach the full potential of IoT.
The main issue IoT devices face is security vulnerabilities. Even though
these IoT devices have inbuilt firewalls , the gateway(normally the home
router) which acts as in interface between the IoT device and the internet
are vulnerable and don’t have inbuilt firewalls. As a result this project focuses
on writing a firewall for gateways like Arduino Uno to which IoT devices can
be connected. The key Idea behind writing a firewall in Arduino is , any
data being transferred to/from the IoT device will pass through the same.

## INTRODUCTION 

### What is an IoT Device ? 

An IoT device is a piece of hardware with a sensor that transmits data from
one place to another over the Internet. Types of IoT devices include wireless
sensors, software, actuators, and computer devices. They can be embedded
into mobile devices, industrial equipment, environmental sensors, medical
devices, and more. Connected IoT devices, which convey usage and other
data, can potentially provide insights that lead companies to cost reductions,
efficiency gains, and new business opportunities.

### Are IoT devices vulnerable ?

IoT security is becoming an increasingly important aspect of IoT device de-
velopment; unsecured IoT devices are an attractive backdoor into an other-
wise secured enterprise network. To efficiently and securely deploy, connect,
and maintain the range of IoT devices and sometimes overwhelming amounts
of data, companies need an IoT device management platform.

## PROBLEM DESCRIPTION

### Threats faced by IoT Devices

IoT security has become the subject of scrutiny after a number of high-profile
incidents where a common IoT device was used to infiltrate and attack the
larger network. Implementing security measures is critical to ensuring the
safety of networks with IoT devices connected to them.IoT security is also
plagued by a lack of industry-accepted standards. While many IoT security
frameworks exist, there is no single agreed-upon framework. Large com-
panies and industry organizations may have their own specific standards,
while certain segments, such as industrial IoT, have proprietary, incompat-
ible standards from industry leaders. The variety of these standards makes
it difficult to not only secure systems, but also ensure inter-operability be-
tween them.Another common issue facing IoT devices is that they are often
resource-constrained and do not contain the compute resources necessary to
implement strong security. As such, many devices do not or cannot offer
advanced security features. For example, sensors that monitor humidity or
temperature cannot handle advanced encryption or other security measures.
Plus, as many IoT devices are ”set it and forget it” – placed in the field or
on a machine and left until end of life – they hardly ever receive security
updates or patches. From a manufacturer’s viewpoint, building security in
from the start can be costly, slow down development and cause the device
not to function as it should. So we plan to build a common firewall into a 
gateway device(Arduino Uno) so that it adds a extra layer of security. 
