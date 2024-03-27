/usr/lib/jvm/jdk1.8.0_301/bin/java -ea -Didea.test.cyclic.buffer.size=1048576 -javaagent:/home/mike/Work/TOOLS/ideaIU-2021.1.1/idea-IU/lib/idea_rt.jar=44941:/home/mike/Work/TOOLS/ideaIU-2021.1.1/idea-IU/bin -Dfile.encoding=UTF-8 -classpath /home/mike/Work/TOOLS/ideaIU-2021.1.1/idea-IU/lib/idea_rt.jar:/home/mike/Work/TOOLS/ideaIU-2021.1.1/idea-IU/plugins/junit/lib/junit5-rt.jar:/home/mike/Work/TOOLS/ideaIU-2021.1.1/idea-IU/plugins/junit/lib/junit-rt.jar:/usr/lib/jvm/jdk1.8.0_301/jre/lib/charsets.jar:/usr/lib/jvm/jdk1.8.0_301/jre/lib/deploy.jar:/usr/lib/jvm/jdk1.8.0_301/jre/lib/ext/cldrdata.jar:/usr/lib/jvm/jdk1.8.0_301/jre/lib/ext/dnsns.jar:/usr/lib/jvm/jdk1.8.0_301/jre/lib/ext/jaccess.jar:/usr/lib/jvm/jdk1.8.0_301/jre/lib/ext/jfxrt.jar:/usr/lib/jvm/jdk1.8.0_301/jre/lib/ext/localedata.jar:/usr/lib/jvm/jdk1.8.0_301/jre/lib/ext/nashorn.jar:/usr/lib/jvm/jdk1.8.0_301/jre/lib/ext/sunec.jar:/usr/lib/jvm/jdk1.8.0_301/jre/lib/ext/sunjce_provider.jar:/usr/lib/jvm/jdk1.8.0_301/jre/lib/ext/sunpkcs11.jar:/usr/lib/jvm/jdk1.8.0_301/jre/lib/ext/zipfs.jar:/usr/lib/jvm/jdk1.8.0_301/jre/lib/javaws.jar:/usr/lib/jvm/jdk1.8.0_301/jre/lib/jce.jar:/usr/lib/jvm/jdk1.8.0_301/jre/lib/jfr.jar:/usr/lib/jvm/jdk1.8.0_301/jre/lib/jfxswt.jar:/usr/lib/jvm/jdk1.8.0_301/jre/lib/jsse.jar:/usr/lib/jvm/jdk1.8.0_301/jre/lib/management-agent.jar:/usr/lib/jvm/jdk1.8.0_301/jre/lib/plugin.jar:/usr/lib/jvm/jdk1.8.0_301/jre/lib/resources.jar:/usr/lib/jvm/jdk1.8.0_301/jre/lib/rt.jar:/home/mike/BOOKS/COMPILER/DRAGON/compiler-front-end/target/test-classes:/home/mike/BOOKS/COMPILER/DRAGON/compiler-front-end/target/classes:/home/mike/.m2/repository/junit/junit/4.13.1/junit-4.13.1.jar:/home/mike/.m2/repository/org/hamcrest/hamcrest-core/1.3/hamcrest-core-1.3.jar com.intellij.rt.junit.JUnitStarter -ideVersion5 -junit4 main.MainTest,parse1
L1:	i = 0
L3:	j = 23
L4:	iffalse i > 23 goto L7
	t1 = 0 * 80
	t2 = j * 8
	t3 = t1 + t2
	t4 = a [ t3 ]
	if t4 < 55.0 goto L6
L7:	iffalse i > 100 goto L5
L6:L8:	j = 0
L9:L11:	t5 = i * 80
	t6 = j * 8
	t7 = t5 + t6
	a [ t7 ] = 0.0
L12:	iffalse j >= 10 goto L9
L13:	goto L10
	goto L9
L10:	iffalse i >= 10 goto L4
L14:	goto L5
	goto L4
L5:	i = 0
L15:L16:	t8 = i * 80
	t9 = i * 8
	t10 = t8 + t9
	a [ t10 ] = 1.0
L17:	iffalse i >= 10 goto L15
L18:	goto L2
	goto L15
L2:
Finished parsing ./src/test/resources/tests/identity3.t
