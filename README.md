# Smart-home-management-system-
A Smart Home Management System using Object-Oriented Programming (OOP) controls and monitors home devices such as lights, fans, doors, and security systems through classes and objects. It applies OOP concepts to make the system secure, efficient, reusable, and easy to manage.
# Smart Home Management System Using OOP (Bullet Points)

* A Smart Home Management System controls and monitors home devices like lights, fans, doors, cameras, and alarms using classes and objects in Object-Oriented Programming (OOP).
* The system includes classes such as **User**, **Device**, **Light**, **Fan**, **Door**, and **SecuritySystem**, where each class has its own data and functions.
* **Inheritance** is used so that all smart devices inherit common properties from a parent **Device** class, reducing code duplication.
* **Encapsulation** protects sensitive data like user credentials and device status by restricting direct access and allowing controlled access through methods.
* **Polymorphism** allows different devices to implement functions like `turnOn()` and `turnOff()` in their own way while using the same method name.
* **Abstraction** hides complex system details and provides a simple interface for users to control all smart home devices easily.
* During **user registration**, validations check unique usernames, strong passwords, and required input fields.
* During **login**, credentials are verified before granting access to the system.
* Device validations ensure only registered devices are controlled, duplicate device IDs are avoided, and invalid commands are rejected.
* Permission checks ensure that only authorized users can access or modify specific devices or settings.
* Overall, the system is secure, scalable, reusable, and easy to maintain due to the use of OOP principles.
