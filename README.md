# pji3

## Hardware project

## Master-Slave Test (BLE MODULES)

### Slave configuration

<ol>
<li>AT+ROLE0 (slave mode)</li>
<li>AT+LADDR (return MAC. Used by master to stablish connection)</li>
<li>AT+TYPE0 (For connections without password)</li>
</ol>

### Master configuration

<ol>
<li>AT+ROLE1 (master mode)</li>
<li>AT+INQ (returns a list of devices scanned)</li>
<li>AT+CONN1 (connect to device in position 1 of the list)</li>
</ol>

After these settings, the two devices will stop flashing their LEDs, signaling the connection establishment.
