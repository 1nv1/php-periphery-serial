# PHP extension

This file backup some information for made a php extension in `C`.

## Links

The next list help me a lot to develop a PHP extension. I started this project
without any knowledge about this and I used this list to work.

* Articles
  * [Writing functions](https://www.hgb-leipzig.de/~uklaus/PHP/internals2.funcs.html) - One core element of an extension are functions which are exported to the PHP userland. Even when you're planning to write object-oriented extensions you are advised to read this chapter as most of the information is valid for methods, too.
  * [PHP 7 Extensions](https://lytrax.io/blog/makeitwork/creating-php7-extensions-linux-windows) - PHP 7 internals have some major changes that break compatibility with all extensions build for prior versions of PHP.
  * [Writing a Hello World](https://zando.io/post/hello-world-php-7-extension/) - Writing a Hello World PHP 7 Extension.
  * [Creating](https://ahungry.com/blog/2016-09-29-Creating-a-php-7-extension.html) - Creating a PHP 7 Extension.
  * [Building](https://docstore.mik.ua/orelly/webprog/php/ch14_03.htm) - Building Your First Extensions.
* Eskeletons
  * [hello-php-extension](https://github.com/jheth/hello-php-extension) - Learning how to write a PHP extension.
  * [skeleton-php-ext](https://github.com/improved-php-library/skeleton-php-ext) - Skeleton project for PHP extension (written in C).
  + [PHP Extension Dynamic Resource](https://gist.github.com/hjanuschka/3ed54e66f017a379cf25) - Gist
* Projects
  * [hdrhistogram-php](https://github.com/beberlei/hdrhistogram-php) - A PHP extension wrapper for the C hdrhistogram API.
  * [libvirt](https://www.redhat.com/archives/libvir-list/2016-April/msg00415.html) - libvirt-php PATCH 13/35] buildable with PHP 7.
* PHP internals
  * [Internal value representation](https://nikic.github.io/2015/05/05/Internal-value-representation-in-PHP-7-part-1.html) - My last article described the improvements to the hashtable implementation that were introduced in PHP 7.
  * [Functions definitions](https://nikic.github.io/2012/03/16/Understanding-PHPs-internal-function-definitions) - Understanding PHP's internal function definitions (PHP's Source Code for PHP Developers - Part 2).
  * [Zend resource](http://www.phpinternalsbook.com/php7/internal_types/zend_resources.html) - The Resource type: zend_resource.
* PHP code internals
  * [Zend API](https://github.com/php/php-src/blob/master/Zend/zend_API.h)
  * [Hastable API](http://www.phpinternalsbook.com/php5/hashtables/hashtable_api.html)
